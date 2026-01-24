# DSU Advanced Series — Video 3 Notes  
## Topic: Rollbacks on Union-Find (DSU with Undo)

**Speaker:** Vivek  
**Series:** Advanced Ideas in DSU  
**Video:** 3 (Rollbacks)  
**Prerequisite:** Basic DSU + Video 2 (Weighted Union-Find)

---

## 1) What is “Rollback” in DSU?

Normal DSU supports:

- **find(x)** → returns the leader/representative of the set containing `x`
- **unite(a, b)** → merges the sets containing `a` and `b`

**Rollback (Undo) DSU** adds:

- **rollback()** → revert DSU back to a previous state (like going back in time)

So if DSU evolves like:

- `State 1 → State 2 → State 3 → State 4`

Rollback lets you do:

- `State 4 → State 3 → State 2 → State 1`

---

## 2) Why not store the whole DSU state each time?

A naive idea:

- store full `parent[]` (and `rank[]`) after every operation  
- rollback = restore old arrays

But this is expensive:

- DSU arrays are size **N**
- if you do **Q** operations, worst case memory/time becomes **O(N·Q)**

Also **path compression** makes it worse because a single `find()` can change many parents at once.

---

## 3) Key Observation: Store only “delta changes”

Instead of saving full arrays, store only what changed.

Example operations:

1. `unite(1,2)` → `parent[2] = 1`
2. `unite(3,4)` → `parent[4] = 3`
3. `unite(2,4)` → merge leaders → `parent[3] = 1`

So the only updates were:

- `parent[2]` changed from `2 → 1`
- `parent[4]` changed from `4 → 3`
- `parent[3]` changed from `3 → 1`

So we can push onto a stack:

- `(2, old_parent=2)`
- `(4, old_parent=4)`
- `(3, old_parent=3)`

### Rollback 1 step:
Pop `(3,3)` → restore `parent[3] = 3`

### Rollback again:
Pop `(4,4)` → restore `parent[4] = 4`

### Rollback again:
Pop `(2,2)` → restore `parent[2] = 2`

So rollback becomes “undo last update”.

---

## 4) Problem: Path Compression breaks rollback efficiency

With **path compression**, `find(x)` can update multiple nodes:

Example chain:

`5 → 4 → 3 → 2 → 1`

After `find(5)`, path compression makes:

`5 → 1`, `4 → 1`, `3 → 1`, ...

So one `find()` can cause **O(N)** parent changes.

Then rollback would require undoing **all** those changes → too expensive.

Worst-case becomes:

- **O(N) per query**
- total **O(N·Q)**

---

## 5) Fix: Don’t use Path Compression

Rollback DSU is usually implemented as:

✅ **Union by Rank/Size**  
❌ **No Path Compression**

Then:

- `find(x)` becomes **O(log N)** (height bounded by rank)
- `unite(a,b)` is **O(log N)**
- rollback is **O(1)** per merge

This is good enough for most competitive programming constraints.

---

## 6) What exactly to store in the rollback stack?

When we merge sets, typically we do:

- attach smaller rank tree under bigger rank tree  
- update rank if needed

So changes are usually:

1. **parent[childRoot]** changes  
2. **rank[root]** might change (only when ranks are equal)

### Minimal info needed to undo a union

Suppose:

- `x` = leader of one set  
- `y` = leader of other set  
- we attach `y` under `x`

Then DSU changes:

- `parent[y] = x`
- maybe `rank[x]` increases by 1 (if ranks equal)

To rollback, we need to restore:

- `parent[y] = y`
- `rank[x] = old_rank_x`

So push onto stack something like:

- `(y, old_rank_x, did_rank_change)`  
  or simply store enough values to restore both fields.

In the video, the key idea described:

- store `y` (the node whose parent was changed)
- store old rank of `x` (so rank can be restored)

Because from current DSU you can get `x = parent[y]`.

---

## 7) Rollback operation (conceptually)

When undoing one union:

1. read `y` and `old_rank_x` from stack  
2. let `x = parent[y]` (current parent)  
3. restore:
   - `rank[x] = old_rank_x`
   - `parent[y] = y`

That reverts DSU by one merge.

---

## 8) Versioning trick

We can treat:

- **stack size** = “current version”

So:

- save `version = stack.size()` at any moment  
- later rollback to that version by popping until stack returns to that size

This allows:

- rollback one step
- rollback many steps
- rollback to a checkpoint

---

## 9) Generalization: Rollback works for other data structures too

Same concept can be applied to:

### Segment Tree Rollback
If an update changes nodes:

- node 1: old value = X
- node 3: old value = Y
- node 6: old value = Z

Store in stack:

- `(1, X)`
- `(3, Y)`
- `(6, Z)`

Rollback means:

- pop and restore each node value

This supports undoing updates efficiently.

---

## 10) Complexity Summary

With rollback DSU (no path compression):

- `find(x)` → **O(log N)**
- `unite(a,b)` → **O(log N)**
- `rollback()` → **O(1)** per union undone
- memory → **O(number_of_unions)**

---

## 11) Main Takeaways

- Rollback DSU lets you revert DSU state efficiently.
- Don’t store full arrays — store only delta changes.
- Path compression makes rollback expensive → avoid it.
- Use union-by-rank/size for logarithmic `find`.
- Stack size can be used as a “version”.

---

## Next Video

Next topic mentioned:

✅ **DSU on Tree**

---

**End of Video 3 Notes**
