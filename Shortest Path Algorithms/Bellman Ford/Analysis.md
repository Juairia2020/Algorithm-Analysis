# Bellman-Ford

## 1. Context

The Bellman-Ford algorithm solves the **Single-Source Shortest Paths (SSSP)** problem. It computes the shortest distance from a source vertex `src` to every reachable vertex in a weighted graph.

Unlike Dijkstra's algorithm, Bellman-Ford supports **negative edge weights**. It can also detect **negative-weight cycles reachable from the source**.

The algorithm repeatedly relaxes every edge. After at most `V - 1` iterations, where `V` is the number of vertices, all shortest distances have been found if no reachable negative-weight cycle exists.

The implementation also stores predecessor information to reconstruct shortest paths and can generate **all shortest paths** when multiple shortest routes exist.

---

## 2. Assumptions

- The graph is weighted.
- The graph may be directed.
- Negative edge weights are allowed.
- A negative-weight cycle reachable from the source makes shortest distances undefined.
- Vertices are numbered from `0` to `V - 1`.
- Unreachable vertices are identified separately from reachable vertices.
- Multiple shortest paths between two vertices may exist.
- Path reconstruction must avoid cycles in the predecessor structure.
- `long long` should be used when edge weights or accumulated distances may be large.

---

## 3. Correctness

### Shortest Distance

After the `k`-th relaxation pass, the algorithm has correctly found the shortest paths that use at most `k` edges.

Any simple shortest path can contain at most `V - 1` edges because a path containing a repeated vertex contains a cycle. If that cycle is not negative, removing it does not increase the path cost.

Therefore, after `V - 1` complete relaxation passes, all shortest distances are correctly computed, provided that no reachable negative-weight cycle exists.

### Edge Relaxation

For an edge `(u, v)` with weight `w`, if:

```text
dist[u] + w < dist[v]
```

then the path through `u` provides a shorter route to `v`.

The algorithm therefore updates:

```text
dist[v] = dist[u] + w
```

and records `u` as a predecessor of `v`.

Repeatedly applying this operation propagates shorter paths through the graph.

### All Shortest Paths

If multiple routes produce the same minimum distance, the implementation stores the corresponding predecessor information so that all shortest paths can be reconstructed.

A reconstructed path is valid because every predecessor relation corresponds to an edge that satisfies the shortest-distance condition.

The implementation also prevents cycles in the predecessor graph during reconstruction, ensuring that path generation terminates.

---

## 4. Negative Cycle Detection

After `V - 1` relaxation passes, every edge is checked once more.

If an edge `(u, v)` still satisfies:

```text
dist[u] + w < dist[v]
```

then a shorter path can still be found.

Since every simple path contains at most `V - 1` edges, such an improvement must involve a cycle.

Because Bellman-Ford only considers vertices reachable from `src`, this indicates a **negative-weight cycle reachable from the source**.

A reachable negative cycle makes the shortest distance undefined because the cycle can be traversed repeatedly to decrease the path cost indefinitely.

Unreachable negative cycles do not affect shortest paths from the chosen source.

---

## 5. Complexity Analysis

Let `V` be the number of vertices and `E` be the number of edges.

### Time Complexity

Bellman-Ford performs at most `V - 1` passes over all `E` edges:

```text
O(VE)
```

The additional negative-cycle detection pass takes:

```text
O(E)
```

Therefore, the overall worst-case complexity remains:

```text
O(VE)
```

If the algorithm terminates early because no distance was updated during a pass, the practical running time can be lower.

### Path Reconstruction

For `K` generated shortest paths with an average path length of `L`:

```text
O(K × L)
```

The number of shortest paths can be exponential in the size of the graph, so generating and storing all shortest paths can become very expensive.

### Space Complexity

The main distance and predecessor structures require:

```text
O(V)
```

space.

The graph itself requires:

```text
O(E)
```

space when represented using an edge list.

Therefore, excluding stored shortest paths:

```text
O(V + E)
```

space is required.

Storing all shortest paths may require substantially more memory.

---

## 6. Advantages and Limitations

### Advantages

- Supports negative edge weights.
- Detects reachable negative-weight cycles.
- Works well with sparse graphs.
- Computes shortest paths from a single source.
- Can reconstruct shortest paths.
- Can be extended to generate all shortest paths.

### Limitations

- `O(VE)` time is slower than Dijkstra's algorithm for graphs with non-negative weights.
- Only computes shortest paths from a chosen source.
- A reachable negative-weight cycle makes shortest distances undefined.
- Storing and printing all shortest paths can be extremely expensive.
- The number of shortest paths may be exponential.
- Zero-weight cycles can produce infinitely many shortest **walks**, so "all shortest paths" should normally refer to simple shortest paths.

---

## 7. When to Use It

Bellman-Ford is a good choice when:

- Shortest paths are required from a **single source**.
- The graph may contain negative edge weights.
- Detection of reachable negative-weight cycles is required.
- The graph is relatively sparse.
- The `O(VE)` running time is acceptable.

For graphs with only non-negative edge weights, Dijkstra's algorithm is generally more efficient.

For finding shortest paths between **all pairs** of vertices, Floyd-Warshall or Johnson's algorithm may be more appropriate.
