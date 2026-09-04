# Kruskal's Algorithm

Kruskal's Algorithm is a greedy algorithm that constructs a Minimum Spanning Tree (MST) by selecting edges in increasing order of weight while avoiding cycles. This implementation uses Disjoint Set Union (DSU) to efficiently detect whether adding an edge would create a cycle.

## Context

- Works on weighted, undirected graphs.
- For disconnected graphs, produces a **Minimum Spanning Forest (MSF)**.
- Uses **DSU** with path compression and union by size.
- Edges are sorted by `wight`.

## Assumptions

- Vertices are numbered from `0` to `V-1`.
- Edge weights are integers.
- The graph is undirected.
- An isolated vertex is treated as a single-vertex tree.

## Greedy Choice

At each step, choose the smallest-weight edge that connects two different components.

- Different components → add the edge and unite them.
- Same component → reject the edge because it creates a cycle.

## Features

- Constructs MST / MSF using Kruskal's Algorithm.
- Detects cycles using DSU.
- Separates the resulting MSF into individual trees.
- Prints vertices and edges of each tree.
- Calculates the weight of each tree and the total MSF weight.
- Handles isolated vertices.
- Uses lexicographic tie-breaking: `(weight, u, v)`.

## When Kruskal is Useful

- When the graph is naturally represented as an edge list.
- For sparse graphs.
- When cycle detection and connected-component management are needed.
- When working with disconnected graphs and Minimum Spanning Forests.

## Limitations

- Works only on undirected graph
- Poor performance in dense graph
- Cannot generate single mst for disconnected graph, generates MSF instead
- Requires edge sorting

## Complexity

- Edge sorting: `O(E log E)`
- DSU operations: `O(E α(V))`
- Tree identification: `O(V α(V))`
- **Overall: `O(E log E)`**
- Space: `O(V + E)`


