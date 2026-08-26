# Johnson's Algorithm

Johnson's Algorithm finds the **shortest distances between every pair of vertices** in a weighted graph.

It combines **Bellman-Ford** and **Dijkstra's Algorithm** to handle graphs that may contain negative edge weights while avoiding the high time complexity of running Bellman-Ford from every vertex.

## Context

Johnson's Algorithm is particularly useful for **sparse graphs** where shortest paths are required between all pairs of vertices.

Dijkstra's Algorithm cannot directly handle negative edge weights, while Floyd-Warshall works well for dense graphs but requires **O(V²)** memory and **O(V³)** time.

Johnson's Algorithm solves this by:

1. Adding a new super-source connected to every vertex with a zero-weight edge.
2. Running Bellman-Ford from the super-source.
3. Using the resulting distances to reweight every edge.
4. Running Dijkstra from every original vertex.
5. Converting the reweighted distances back to their original values.

## Assumptions

- The graph is **directed**.
- The graph may contain **negative edge weights**.
- The graph must not contain a **negative-weight cycle**.

## Correctness

### Lemma 1: Reweighting produces non-negative edge weights

For every edge `(u,v)`:

```text
h[v] <= h[u] + w(u,v)
```

because `h[v]` is the shortest distance from the super-source to `v`.

Therefore:

```text
w'(u,v) = w(u,v) + h[u] - h[v] >= 0
```

So Dijkstra can safely operate on the reweighted graph.

### Lemma 2: Reweighting preserves the ordering of path costs

For a path:

```text
P = v₀ → v₁ → ... → vₖ
```

its reweighted cost is:

```text
Σ(w(vᵢ,vᵢ₊₁) + h[vᵢ] - h[vᵢ₊₁])
```

The potential terms telescope, leaving:

```text
cost'(P) = cost(P) + h[v₀] - h[vₖ]
```

For a fixed source and destination, the added term is constant. Therefore, the ordering of path costs is preserved and the shortest path remains the same.

### Theorem: Johnson's Algorithm is Correct

Bellman-Ford computes the potentials and detects negative-weight cycles. If no negative cycle exists, reweighting produces non-negative edge weights while preserving shortest paths.

Dijkstra therefore correctly finds the shortest path for every source in the reweighted graph. Finally,

```text
d(u,v) = d'(u,v) - h[u] + h[v]
```

recovers the original shortest-path distances.

Hence, Johnson's Algorithm correctly computes the shortest distances between every pair of vertices.

## Complexity

Let:

- `V` = number of vertices
- `E` = number of edges

### Bellman-Ford

```text
O(VE)
```

### Reweighting

Every edge is processed once:

```text
O(E)
```

### Dijkstra

Dijkstra is run `V` times.

Using a binary heap:

```text
O(E log V)
```

per source.

Therefore, all Dijkstra runs require:

```text
O(VE log V)
```

### Overall Complexity

```text
O(VE + E + VE log V)
```

which simplifies to:

```text
O(VE log V)
```

for the binary-heap implementation.

### Space Complexity

The graph uses:

```text
O(V + E)
```

The distance, parent, and path information for one Dijkstra run requires additional space.

The implementation does not permanently store all shortest paths, so the main space requirement remains:

```text
O(V + E)
```

## Considerations

- It is generally more suitable for **sparse graphs**.
- For dense or complete graphs, Floyd-Warshall can be competitive or preferable because `E = O(V²)`.
- This particular implementation stores **one shortest path** for each source-destination pair.
