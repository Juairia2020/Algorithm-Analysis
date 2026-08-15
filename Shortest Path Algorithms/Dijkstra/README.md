# Dijkstra 

* Shortest distance from `src` to `dest`.
* Reconstructs **all shortest paths**
* Detects unreachable destinations.

## Complexity

* Dijkstra: **O(E log V)**.
* Space: **O(V + E)** excluding stored paths.
* Path reconstruction: **O(K × L)**, where `K` = number of shortest paths and `L` = average path length.
* Number of shortest paths can be exponential.

## Considerations

* Edge weights must be > 0
* Graph is currently undirected
* Storing/printing all shortest paths can become extremely expensive.
* Uses `int` for distances
