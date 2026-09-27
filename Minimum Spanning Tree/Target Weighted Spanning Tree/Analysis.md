# Finding a Target-Weighted Spanning Tree

## Problem Description

Given a **fully connected weighted graph**, find a spanning tree whose total edge weight is exactly equal to a given target value `M`.

The problem is solved using a **subset/backtracking approach**. Each edge is considered as either:

* **Taken**: include the edge in the spanning tree.
* **Skipped**: do not include the edge.

Since not every subset of edges forms a valid spanning tree, **DSU (Disjoint Set Union)** is used to detect cycles while constructing the solution.

---

## Assumptions

* The graph is fully connected.
* Each edge has a weight.
* The vertices are numbered from `0` to `V-1`.
* A spanning tree must contain exactly `V - 1` edges.
* The target weight is an integer.
* The current implementation assumes **non-negative/positive edge weights** for the target-based pruning condition.

---

## Solution Tuple

A solution is represented as a set of edges:

```text
E = [(u₁, v₁), (u₂, v₂), ..., (uₖ, vₖ)]
```

where each selected edge belongs to the original graph.

For every selected edge:

```text
(uᵢ, vᵢ) ∈ Edges
```

---

## Constraints

### Explicit Constraint

Every selected edge must belong to the graph.

```text
(uᵢ, vᵢ) ∈ Edges
```

### Implicit Constraints

The selected edges must satisfy:

1. **Target weight constraint**

```text
Σ wᵢ = M
```

2. **No cycle**

The selected edges must not form a cycle.

3. **Spanning tree size**

```text
|E| = V - 1
```

Together, these conditions ensure that the selected edges form a spanning tree with the required total weight.

---

## Approach

The algorithm treats the problem as a **subset search with backtracking**.

For every edge, there are two choices:

```text
                 Current Edge
                  /        \
               TAKE        SKIP
                /            \
          Add edge        Ignore edge
             |
        Continue search
```

The recursion explores these choices until either:

* a valid target-weighted spanning tree is found, or
* all possibilities are exhausted.

## Complexity Analysis

Let:

* `E` = number of edges
* `V` = number of vertices

### Time Complexity

Each edge has two possibilities:

```text
TAKE
SKIP
```

Therefore, in the worst case, the recursion explores approximately:

```text
O(2ᴱ)
```

subsets.

For every TAKE operation, the current implementation creates a copy of the DSU:

```cpp
DSU temp_dsu = dsu;
```

Copying the DSU requires:

```text
O(V)
```

time.

Therefore, a safe worst-case bound for the current implementation is:

```text
O(2ᴱ · V)
```

DSU `find` and `unite` operations themselves are approximately constant amortized time with path compression and union by size:

```text
O(α(V))
```

where `α` is the inverse Ackermann function.

However, the DSU copying dominates the per-branch cost in this implementation.

### Space Complexity

The recursion depth can reach `E`.

Each recursive call contains its own DSU copy of size `O(V)`.

Therefore, the worst-case auxiliary stack space is:

```text
O(EV)
```

The selected spanning tree requires:

```text
O(V)
```

space.

---

## Important Limitation

The algorithm is  **exponential** in the number of edges.

The pruning conditions can significantly reduce the search space for many inputs, but they do not change the worst-case complexity:

```text
O(2ᴱ · V)
```

---


