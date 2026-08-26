# Floyd-Warshall Algorithm

## 1. Context

The Floyd-Warshall algorithm solves the **All-Pairs Shortest Paths (APSP)** problem. It computes the shortest distance between every pair of vertices in a weighted graph.

Unlike Dijkstra's algorithm, it supports negative edge weights. However, shortest paths are not well-defined when the graph contains a negative-weight cycle.

The algorithm gradually allows each vertex to be used as an intermediate vertex. For vertices `i`, `j`, and `k`:

```text
D[i][j] = min(D[i][j], D[i][k] + D[k][j])
```

The implementation also stores the corresponding paths.

## 2. Assumptions

- The graph is weighted.
- Negative edge weights are allowed.
- The graph must not contain a negative-weight cycle.


## 3. Correctness

After iteration `k`, `D[i][j]` stores the shortest path from `i` to `j` whose intermediate vertices are among `0, 1, ..., k`.

When considering vertex `k`, every possible shortest path is one of two types:

1. It does not pass through `k`, so its current value `D[i][j]` remains valid.
2. It passes through `k`, so its cost is `D[i][k] + D[k][j]`.

The algorithm chooses the smaller of these two values. Therefore, after all vertices have been considered, `D[i][j]` contains the shortest distance between every pair of vertices.

When a shorter path is found through `k`, the stored path is formed by combining the paths from `i` to `k` and from `k` to `j`. Thus, path information remains consistent with the distance matrix.


## 4. Negative Cycle Detection

Initially, every diagonal entry satisfies:

```text
D[i][i] = 0
```

After the algorithm finishes, if:

```text
D[i][i] < 0
```

for any vertex `i`, then the graph contains a negative-weight cycle reachable from `i`.

In that case, shortest paths involving the cycle are undefined because repeatedly traversing the cycle can reduce the path cost indefinitely.


## 5. Complexity Analysis

Let `V` be the number of vertices.

### Time Complexity

The algorithm uses three nested loops. Therefore:

```text
O(V^3)
```

Negative-cycle detection takes `O(V)` time and does not affect the overall complexity.

If complete paths are copied during updates, the practical running time may be higher because of path-copying overhead.

### Space Complexity

The distance matrix requires:

```text
O(V^2)
```

space.

The path matrix may require additional memory depending on the number and length of stored paths. Without explicit path storage, Floyd-Warshall uses `O(V²)` space.


## 7. Advantages and Limitations

### Advantages

- Computes shortest paths between all vertex pairs.
- Supports negative edge weights.
- Detects negative-weight cycles.
- Has a simple dynamic programming structure.
- Can reconstruct shortest paths.

### Limitations

- `O(V³)` time is expensive for large graphs.
- Requires `O(V²)` space, even for sparse graphs.
- Negative-weight cycles make shortest paths undefined.
- Storing complete paths increases memory usage.

For large sparse graphs, algorithms such as Johnson's algorithm are usually more efficient.
