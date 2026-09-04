# Prim's Algorithm

Prim's Algorithm finds a **Minimum Spanning Tree (MST)** of a weighted, undirected graph.

It is a **greedy algorithm** that starts from a vertex and repeatedly adds the minimum-weight edge that connects the current tree to a vertex outside it.

For disconnected graphs, applying Prim separately to each connected component produces a **Minimum Spanning Forest (MSF)**.

## Context

Prim's Algorithm is useful when a minimum-cost structure connecting all vertices is required.

It is commonly used in:

- Network design
- Road and infrastructure planning
- Electrical and communication networks
- Connecting locations with minimum total cost

Unlike shortest-path algorithms, Prim minimizes the **total weight of the selected edges** rather than the distance from one source to other vertices.

## Greedy Choices

At each step, Prim makes the following greedy choices:

1. Select the unvisited vertex with the **smallest `key` value**.
2. Add the corresponding minimum-weight edge to the MST.
3. Update the cheapest known connection for each neighboring unvisited vertex.

The key idea is:

> Always choose the cheapest edge connecting the current MST to a vertex outside the MST.

Prim does **not** simply choose the cheapest edge from the most recently added vertex. The choice is made among all edges connecting the current MST to vertices outside it.

## Assumptions

- The graph is **weighted**.
- The graph is **undirected**.
- A connected graph produces a single MST.
- A disconnected graph produces a Minimum Spanning Forest.
- Edge weights may be positive, zero, or negative.
- An MST contains all vertices and exactly `V - 1` edges.
- Each connected component of a Minimum Spanning Forest has its own MST.

## Features

This implementation:

- Uses an **adjacency list** to represent the graph.
- Uses a `set` to maintain vertices according to their current `key`.
- Finds an MST for connected graphs.
- Handles disconnected graphs by producing a **Minimum Spanning Forest**.
- Handles isolated vertices as one-vertex trees with weight `0`.
- Prints the selected MST edges.
- Calculates the total MST / forest weight.

## Limitations

- Prim is designed for **weighted, undirected graphs**.
- A standard implementation assumes the graph is connected. For disconnected graphs, a single MST does not exist.
- Prim finds an MST but does not inherently determine whether the MST is **unique**.
- Prim does not inherently find the **lexicographically smallest MST** when multiple MSTs exist.
- Prim does not detect whether the **original graph contains cycles**.
- The performance depends on the data structure used to select the minimum-key vertex.


## Complexity

```text
Time:  O(E log V)
Space: O(V + E)
```

The `O(log V)` factor comes from `set` insertion and deletion.

## Considerations

- Prim is particularly convenient when the graph is represented using an **adjacency list**.
- For dense graphs, an adjacency-matrix implementation with linear minimum selection can achieve `O(V²)` time.
- A binary-heap (`priority_queue`) implementation also has `O(E log V)` asymptotic time, although it can have better practical performance than `set`.
- For problems involving **cycle detection, MST uniqueness, or lexicographically smallest MST**, Kruskal's Algorithm with DSU can be more convenient.
- The resulting MST is not necessarily unique when multiple edges have the same weights.