# DSU (Disjoint Set Union) / Union-Find — In-depth Notes (Video 1)

**Video Link:** https://youtu.be/kIe2QkhiAdI  
**Instructor:** Vivek  
**Topic:** DSU fundamentals + small-to-large trick + union-find optimizations (rank/size + path compression)

---

## ✅ What is DSU?

**DSU (Disjoint Set Union)** is a data structure used to maintain a collection of **disjoint sets** (sets with no common elements).

Example of disjoint sets:

- Set A = {1, 3, 5}
- Set B = {2, 6}
- Set C = {4, 8, 7}

These sets are **disjoint** because no element appears in more than one set.

---

## 🎯 Operations DSU must support

### 1) `union(x, y)` / `unite(x, y)`
Merge the sets containing `x` and `y`.

> Important: `union(5, 4)` means **merge the entire set containing 5** with **the entire set containing 4**, not just the two elements.

---

### 2) `find(x)`
Return the **representative/leader** of the set that contains `x`.

---

### 3) `checkSame(x, y)`
Check if `x` and `y` belong to the same set.

This can be done using:
```text
checkSame(x, y) = (find(x) == find(y))
```

---

### 4) (Extra info often required) `count(x)`
Return size of the set containing `x`.

---

## ❌ Why naive approaches are slow?

### Naive idea:
Store sets in arrays and maintain membership.

Problem:
- `find` and `checkSame` can be fast
- BUT `union` becomes expensive because you may need to **rebuild/relocate many elements** each time

Worst-case per union: **O(N)**  
Over many queries: can become **O(N²)** type behavior

---

# Approach 1 — Maintaining explicit sets (Small-to-Large Trick)

## 🧠 Idea
Maintain:
- `customSet[id]` → the set of elements in that component
- `elementIn[x]` → which set/component `x` currently belongs to

Example:
- `elementIn[5] = 1` means element `5` belongs to set ID `1`

---

## 🔥 Problem with naive merging
If we merge sets randomly, we might repeatedly move large sets into smaller sets.

Worst case example:
- Merge size 1 into 1 → size 2
- Merge size 2 into 1 → move 2 elements
- Merge size 3 into 1 → move 3 elements
- ...
Total moves becomes ~ **O(N²)**

Since each move in a `set` costs **log N**:
Total can become **O(N² log N)**

---

## ✅ Small-to-Large Optimization
Always merge the **smaller set into the larger set**.

### Union strategy:
If merging setX and setY:
- if `size(setX) < size(setY)` → swap
- move all elements of smaller into bigger

---

## 📌 Why Small-to-Large works (Key Proof Idea)
Focus on a single element `x`.

Each time `x` moves:
- it moves from smaller set to bigger set
- so the size of its new set at least **doubles**

Example:
- starts in size 1
- after 1 move → size ≥ 2
- after 2 moves → size ≥ 4
- after 3 moves → size ≥ 8
- ...

So `x` can move at most:
```text
log₂(N) times
```

Each move costs:
- `O(log N)` for insertion into a balanced BST set

So per element:
```text
O(log N * log N) = O(log² N)
```

Total for all elements:
```text
O(N log² N)
```

---

## 🧾 Small-to-Large Implementation (Template Style)

### Data structures:
```cpp
vector<int> elementIn;           // elementIn[x] = setID of x
vector< set<int> > customSet;    // customSet[setID] stores elements
```

### Init:
Each element is in its own set.
```cpp
for (int i = 1; i <= n; i++) {
    elementIn[i] = i;
    customSet[i].insert(i);
}
```

### Find:
```cpp
int findSet(int x) {
    return elementIn[x];
}
```

### Union (small-to-large):
```cpp
void unite(int x, int y) {
    int setX = elementIn[x];
    int setY = elementIn[y];

    if (setX == setY) return;

    if (customSet[setX].size() < customSet[setY].size())
        swap(setX, setY); // ensure setX is larger

    for (auto element : customSet[setY]) {
        elementIn[element] = setX;
        customSet[setX].insert(element);
    }
    customSet[setY].clear();
}
```

---

## ⚡ Improvement note (Important)
If you replace `set<int>` with `vector<int>`, insertion becomes `O(1)` instead of `O(log N)`.

Then complexity becomes:
```text
O(N log N)  (amortized)
```

But `set` is useful when you need ordering / lower_bound / upper_bound.

---

# Approach 2 — Union-Find (Tree Representation)

Instead of storing explicit sets, DSU stores a **parent array** forming trees.

---

## 🌳 Representation
Each set is a tree.
- Every node points to a **parent**
- The root is the **leader/representative**
- Root points to itself

Example:
```text
parent[1] = 1  (root)
parent[3] = 1
parent[5] = 3
```

So `find(5)` follows:
```text
5 -> 3 -> 1
```

Leader = `1`

---

## ✅ Core arrays
```cpp
vector<int> parent;
vector<int> rank;   // OR size
```

---

## Operation: Find (Naive)
```cpp
int find(int x) {
    if (parent[x] == x) return x;
    return find(parent[x]);
}
```

### Problem
If unions are done badly, tree can become a long chain:

```text
4 -> 3 -> 2 -> 1
```

Then `find(4)` becomes **O(N)**.

---

## ✅ Optimization 1: Union by Rank / Height
Always attach the **smaller height tree** under the **larger height tree**.

### Union by rank logic:
- find rootX, rootY
- if rank[rootX] < rank[rootY] → swap
- parent[rootY] = rootX
- if ranks equal → rank[rootX]++

### Code:
```cpp
void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return;

    if (rank[rootX] < rank[rootY])
        swap(rootX, rootY);

    parent[rootY] = rootX;

    if (rank[rootX] == rank[rootY])
        rank[rootX]++;
}
```

### Complexity
With union-by-rank:
```text
find = O(log N)
union = O(log N)  (because union calls find)
```

---

## ✅ Optimization 2: Union by Size
Instead of rank, maintain component sizes.

- attach smaller size component under bigger size component
- update size of leader

### Code:
```cpp
vector<int> sz;

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return;

    if (sz[rootX] < sz[rootY])
        swap(rootX, rootY);

    parent[rootY] = rootX;
    sz[rootX] += sz[rootY];
}
```

### Why size is useful?
Because many problems ask:
- size of connected component
- number of nodes in the same group

So size gives extra information.

---

## ✅ Optimization 3: Path Compression
When calling `find(x)`, compress the path so future queries are faster.

### Code (classic):
```cpp
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}
```

### Example
Before:
```text
4 -> 3 -> 2 -> 1
```

After calling `find(4)`:
```text
4 -> 1
3 -> 1
2 -> 1
```

Tree becomes almost flat.

---

## 🚀 Best DSU = Union by Rank/Size + Path Compression
If you use **both**:
- union by rank/size
- path compression

Then complexity becomes:
```text
~ O(α(N))   (inverse Ackermann)
```

In video it’s described as extremely small (almost constant), often <= 5 for CP constraints.

---

## ✅ Final DSU Template (Recommended)

### Using Size + Path Compression
```cpp
struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;

        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }

    int size(int x) {
        return sz[find(x)];
    }
};
```

---

## 🧠 Key Takeaways
- DSU solves dynamic connectivity queries efficiently.
- `checkSame(x, y)` is simply `find(x) == find(y)`.
- Small-to-large reduces total movement by ensuring each element moves at most `log N` times.
- Union-Find is the best practical solution:
  - union by size/rank keeps trees shallow
  - path compression flattens trees during finds
  - overall complexity becomes almost constant

---

## ❓ Quick Revision Questions
1. Why does naive merging of sets become O(N²)?
2. In small-to-large, why does an element move only O(log N) times?
3. What does `find(x)` return in union-find?
4. Why does union-by-rank prevent long chains?
5. What does path compression change inside the parent array?
6. Why is union-by-size preferred in many problems?

---
