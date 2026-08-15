# Bellman-Ford

## Features

* Finds the **shortest distance and all shortest paths** from `src` to `dest`.
* Handles **negative edge weights**.
* Detects **reachable negative-weight cycles**.
* Detects unreachable destinations.
* Protects path reconstruction from **cycles in the parent graph**.

## Complexity

* Bellman-Ford: **O(VE)** worst case.
* Space: **O(V + E)** excluding stored paths.
* Path reconstruction: **O(K × L)**, where `K` = number of generated paths and `L` = average path length.
* The number of shortest paths can be exponential.

## Considerations

* Much slower than Dijkstra for graphs with non-negative weights.
* Storing/printing all shortest paths can be extremely expensive.
* `int` distances can overflow with very large weights; use `long long` if necessary.
* Zero-weight cycles can make "all shortest paths" problematic because infinitely many shortest **walks** may exist.
