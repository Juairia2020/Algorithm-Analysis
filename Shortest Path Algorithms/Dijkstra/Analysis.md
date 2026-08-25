# Dijkstra

## 1. Context

Dijkstra's algorithm solves the **Single-Source Shortest Paths (SSSP)** problem for weighted graphs with **non-negative edge weights**.

Given a source vertex `src`, it computes the shortest distance from `src` to every reachable vertex. The implementation can also reconstruct **all shortest paths** when multiple shortest routes have the same minimum cost.

The algorithm repeatedly selects the unvisited vertex with the smallest known distance and relaxes its outgoing edges.

## 2. Assumptions

- The graph is weighted.
- Edge weights must be **non-negative**.
- Zero-weight edges are allowed.
- The current implementation uses an undirected graph.
- The graph may contain multiple shortest paths between two vertices.
- Unreachable destinations are detected.
- Vertices are numbered from `0` to `V - 1`.
- `long long` should be used when edge weights or accumulated distances may be large.

## 3. Correctness

### Greedy Choice

At each step, Dijkstra's algorithm selects the unvisited vertex `u` with the smallest tentative distance.

Because all edge weights are non-negative, any alternative path reaching `u` through another unvisited vertex must have a cost at least as large as the current distance of `u`.

Therefore, once `u` is selected, its shortest distance is final.

### Edge Relaxation

For an edge `(u, v)` with weight `w`, the algorithm checks whether reaching `v` through `u` is shorter:

```text
dist[u] + w < dist[v]
```

If so, the distance is updated:

```text
dist[v] = dist[u] + w
```

If:

```text
dist[u] + w == dist[v]
```

then another shortest path to `v` has been found and the corresponding predecessor information is stored.

### Termination

The algorithm continues until all reachable vertices have been finalized or the priority queue becomes empty.

Therefore, after termination, the stored distance of every reachable vertex is its shortest distance from `src`.

The predecessor information can then be used to reconstruct the corresponding shortest paths.

## 4. Unreachable Vertices

If a vertex cannot be reached from `src`, its distance remains infinity.

Such a vertex is reported as unreachable rather than attempting to reconstruct a path.

Therefore, Dijkstra's algorithm naturally handles disconnected graphs.


## 5. Complexity Analysis

Let `V` be the number of vertices and `E` be the number of edges.

### Time Complexity

Using an adjacency list and a binary heap / priority queue:

```text
O(E log V)
```

Each relevant vertex or edge operation involves priority-queue operations with logarithmic cost.

For an undirected graph, each edge appears in both adjacency lists, but this does not change the asymptotic complexity.

### Path Reconstruction

For `K` generated shortest paths with an average path length of `L`:

```text
O(K × L)
```

The number of shortest paths can be exponential in the size of the graph, so generating and storing all shortest paths can become extremely expensive.

### Space Complexity

The graph requires:

```text
O(V + E)
```

space when represented using an adjacency list.

The distance and predecessor structures require:

```text
O(V)
```

additional space.

Therefore, excluding stored paths:

```text
O(V + E)
```

space is required.

Storing all shortest paths may require substantially more memory.

## 6. Advantages and Limitations

### Advantages

- Efficient for graphs with non-negative edge weights.
- Computes shortest paths from a single source.
- Works well with sparse graphs.
- Can reconstruct shortest paths.
- Can be extended to generate all shortest paths.
- Detects unreachable destinations.

### Limitations

- Cannot correctly handle negative edge weights.
- The current implementation is designed for undirected graphs.
- `O(E log V)` is not suitable for every graph size or representation.
- Storing and printing all shortest paths can be extremely expensive.
- The number of shortest paths may be exponential.
- `long long` should be used for very large edge weights or accumulated distances.

## 7. When to Use It

Dijkstra's algorithm is a good choice when:

- Shortest paths are required from a **single source**.
- All edge weights are **non-negative**.
- The graph is relatively sparse.
- Efficient shortest-path computation is required.
- An `O(E log V)` solution is acceptable.

For graphs containing negative edge weights, **Bellman-Ford** is more appropriate.

For finding shortest paths between **all pairs** of vertices, **Floyd-Warshall** or **Johnson's algorithm** may be more appropriate.
