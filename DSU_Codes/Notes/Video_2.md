# DSU Level 2 — Weighted Union-Find (Union-Find with Differences) — In-depth Notes (Video 2)

**Video Link:** https://youtu.be/oLsk9w94aY4  
**Instructor:** Vivek  
**Topic:** Weighted DSU / Union-Find with equations of form `x[a] - x[b] = c`

---

## ✅ What is Weighted Union-Find?

Normal DSU helps answer:

- Are `a` and `b` in the same component?
- Merge two components

But it **cannot** store extra information like:

> If `a` and `b` are related, what is `x[a] - x[b]`?

Weighted DSU extends DSU to store **relative differences** between nodes.

---

# 🎯 Problem Statement (from video)

There are `n` variables:

```text
x1, x2, x3, ..., xn
```

We receive queries of two types:

---

## Query Type 1: `1 a b c`
Add information to the knowledge base:

```text
x[a] - x[b] = c
```

### Possible outcomes:
1. **Already related and consistent**
   - The implied difference already equals `c`
   - Do nothing

2. **Already related but inconsistent**
   - The implied difference is NOT equal to `c`
   - Report **"inconsistent"** and ignore

3. **Not related**
   - Add this equation to knowledge base
   - This connects two components

---

## Query Type 2: `2 a b`
Print the value of:

```text
x[a] - x[b]
```

### Possible outcomes:
1. If `a` and `b` are connected → print difference
2. If not connected → print `"can't say"` / `"no information"`

---

# 🧪 Example Walkthrough (Video Example)

Given equations:

1) `x2 - x3 = 5`  
2) `x3 - x5 = 2`  
3) `x2 - x4 = 3`

Now consider query:

### `1 2 5 8`  → add `x2 - x5 = 8`
But from existing info:

```text
x2 - x3 = 5
x3 - x5 = 2
----------------
x2 - x5 = 7
```

But query says `8`, so this is **inconsistent**.

✅ Output: `inconsistent` and ignore it.

---

### `1 2 5 7` → add `x2 - x5 = 7`
This matches implied info, so it's consistent.

---

### `2 5 4` → ask `x5 - x4`
We know:

```text
x2 - x5 = 7
x2 - x4 = 3
```

We want:

```text
x5 - x4
```

Rearrange:

```text
(x2 - x4) - (x2 - x5) = x5 - x4
3 - 7 = -4
```

✅ Answer: `-4`

---

### `2 1 5` → ask `x1 - x5`
No information about `x1`.

✅ Output: `"can't say"`

---

# 🧠 Key Idea: Model Equations as Weighted Edges

For equation:

```text
x[a] - x[b] = c
```

Represent as a directed edge:

```text
a -> b  with weight = c
```

Meaning:

```text
x[a] - x[b] = weight(a -> b)
```

---

## 🔁 Important Observations

### 1) Direction can be flipped
If:

```text
x[a] - x[b] = c
```

Then also:

```text
x[b] - x[a] = -c
```

So edge can be reversed with negated weight.

---

### 2) Path sums give differences
If we have:

```text
x1 - x2 = 2
x2 - x3 = 3
```

Then:

```text
x1 - x3 = 5
```

So we can “short-circuit” via sums along a path.

---

# ❌ Why plain graph is not enough?

If we just store arbitrary edges:
- structure may not be a tree
- multiple paths create cycles
- DSU requires each node to ultimately point to a single leader/root

So we need a DSU-like tree structure, but **with weights**.

---

# ✅ Weighted DSU Structure

We maintain:

- `parent[x]` → parent of node `x`
- `weight[x]` → weight from node `x` to its parent

### Meaning of weight:
If:

```text
parent[x] = p
weight[x] = w
```

Then:

```text
x[x] - x[p] = w
```

So `weight[x]` always represents:

```text
x[x] - x[parent[x]]
```

---

# 🔍 Weighted Find Operation

In normal DSU:

```cpp
find(x) -> root
```

In weighted DSU we want:

```text
find(x) -> (root, cost)
```

Where:

- `root` = representative of component
- `cost` = `x[x] - x[root]`

---

## 📌 How cost is computed
Suppose:

```text
x -> y  (weight = d)
```

And we already know from recursion:

```text
find(y) -> (leader, c')
where c' = x[y] - x[leader]
```

Then:

```text
x[x] - x[leader]
= (x[x] - x[y]) + (x[y] - x[leader])
= d + c'
```

So:

```text
leader(x) = leader(y)
cost(x)   = weight[x] + cost(y)
```

---

## ✅ Find with Path Compression (IMPORTANT)

Just like normal DSU, we compress paths.

But now, while compressing, we must update weights too.

### Pseudocode:
```cpp
pair<int,long long> find(int x) {
    if (parent[x] == x) return {x, 0};

    auto [root, costToRootOfParent] = find(parent[x]);

    // update weight[x] to directly connect x -> root
    weight[x] += costToRootOfParent;
    parent[x] = root;

    return {parent[x], weight[x]};
}
```

After compression:
- `parent[x]` becomes the root
- `weight[x]` becomes `x[x] - x[root]`

---

# 🔗 Union Operation (Adding an equation)

We want to add:

```text
x[a] - x[b] = c
```

Let:

```text
find(a) -> (ra, ca)   where ca = x[a] - x[ra]
find(b) -> (rb, cb)   where cb = x[b] - x[rb]
```

---

## Case 1: Same component (ra == rb)
Then the difference is already determined:

```text
x[a] - x[b] = (x[a] - x[root]) - (x[b] - x[root])
           = ca - cb
```

So we check:

```text
ca - cb == c
```

- If true → consistent
- Else → inconsistent

---

## Case 2: Different components (ra != rb)
We must connect roots so that the equation holds.

Assume we attach:

```text
rb -> ra
```

We need to set:

```text
parent[rb] = ra
```

And we must compute `weight[rb]` such that the new DSU maintains:

```text
x[a] - x[b] = c
```

---

### Derivation for weight[rb]
We know:

```text
x[a] - x[b] = c
x[a] = x[ra] + ca
x[b] = x[rb] + cb
```

Substitute:

```text
(x[ra] + ca) - (x[rb] + cb) = c
x[ra] - x[rb] = c - ca + cb
```

But if we connect `rb -> ra`, then:

```text
weight[rb] = x[rb] - x[ra]
```

So:

```text
x[rb] - x[ra] = -(x[ra] - x[rb])
              = -(c - ca + cb)
              = -c + ca - cb
```

✅ Final formula:

```text
weight[rb] = ca - cb - c
```

---

## ⚖️ Union by Rank/Size
Same as DSU:
- attach smaller tree under larger tree
- but update formula accordingly depending on direction

If you swap roots, the weight formula must be recomputed carefully.

---

# 🧾 Answering Query Type 2 (Difference Query)

To answer:

```text
x[a] - x[b]
```

We do:

```text
find(a) -> (ra, ca)
find(b) -> (rb, cb)
```

If `ra != rb`:
- print `"can't say"`

Else:
```text
x[a] - x[b] = ca - cb
```

---

# ✅ Complete Weighted DSU Template (C++)

```cpp
struct WeightedDSU {
    int n;
    vector<int> parent, rnk;
    vector<long long> w; // w[x] = x[x] - x[parent[x]]

    WeightedDSU(int n): n(n) {
        parent.resize(n + 1);
        rnk.assign(n + 1, 0);
        w.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    pair<int,long long> find(int x) {
        if (parent[x] == x) return {x, 0};

        auto [root, costParent] = find(parent[x]);
        w[x] += costParent;
        parent[x] = root;

        return {parent[x], w[x]};
    }

    // Adds constraint: x[a] - x[b] = c
    // Returns false if inconsistent
    bool unite(int a, int b, long long c) {
        auto [ra, ca] = find(a);
        auto [rb, cb] = find(b);

        if (ra == rb) {
            // check consistency
            return (ca - cb == c);
        }

        // union by rank
        if (rnk[ra] < rnk[rb]) {
            swap(ra, rb);
            swap(ca, cb);
            c = -c; // because swapping a and b flips equation
        }

        // attach rb under ra
        parent[rb] = ra;

        // weight[rb] = x[rb] - x[ra]
        w[rb] = ca - cb - c;

        if (rnk[ra] == rnk[rb]) rnk[ra]++;
        return true;
    }

    // returns optional difference if connected
    bool diff(int a, int b, long long &ans) {
        auto [ra, ca] = find(a);
        auto [rb, cb] = find(b);
        if (ra != rb) return false;
        ans = ca - cb;
        return true;
    }
};
```

---

# ⚠️ Common Mistakes / Gotchas

### 1) Wrong meaning of weight[]
Always define weight consistently, e.g.

```text
w[x] = x[x] - x[parent[x]]
```

If you change this definition, all formulas change.

---

### 2) Forgetting to update weights during path compression
In weighted DSU, path compression must update weights, not just parent.

---

### 3) Swapping roots without adjusting equation sign
If you swap `(a,b)` during union-by-rank, equation:

```text
x[a] - x[b] = c
```

becomes:

```text
x[b] - x[a] = -c
```

So you must flip sign.

---

### 4) Using int for weights
Differences can grow large → use `long long`.

---

# ✅ Summary (3 Key Things)

1. **Store parent + edge weight**
   - `parent[x]`
   - `w[x] = x[x] - x[parent[x]]`

2. **Find returns (leader, cost)**
   - leader = root
   - cost = `x[x] - x[root]`

3. **Union merges leaders with computed weight**
   - check inconsistency if already connected
   - otherwise connect roots with correct `w[rootChild]`

---

## ❓ Revision Questions
1. What does `w[x]` represent in weighted DSU?
2. What does `find(x)` return in weighted DSU?
3. How do you compute `x[a] - x[b]` if both are connected?
4. When do we say a constraint is inconsistent?
5. Why must weights be updated during path compression?
6. Derive the formula for `w[rb]` when attaching `rb -> ra`.

---
