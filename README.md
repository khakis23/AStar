# A* Pathfinding Algorithm
### Author: Tyler Black
A fast lightweight implementation of the A* pathfinding algorithm in C++,
designed to be easily integrated into larger applications, with optional
terminal visualization.

## How A* Works

A* is a shortest-path search algorithm that finds an efficient route between two
points by combining the actual distance traveled with an estimate of the distance
remaining. Brute-force search grows exponentially—approximately $b^d$ states for
branching factor $b$ and depth $d$—so A* reduces the search effort by expanding
only the lowest cost nodes.

A* operates on a graph where nodes represent positions and edges represent
possible movements. In an unweighted grid, each move costs $1$. A* evaluates each
node using:

$$f(n) = g(n) + h(n)$$

Here, $g(n)$ is the cost from the start to the current node, and $h(n)$ is an
estimate of the distance to the goal.

Common choices for $h(n)$ include Manhattan distance:

$$|p_x - q_x| + |p_y - q_y|$$

and Euclidean distance:

$$\sqrt{(p_x - q_x)^2 + (p_y - q_y)^2}$$

The term $g(n)$ increases as the path grows, while $h(n)$ guides the search
toward the goal. This combination allows A* to avoid exploring unnecessary areas
of the graph.

A* stores nodes in a priority queue ordered by their $f(n)$ values, making each
push or pop operation $O(\log N)$, where $N$ is the number of nodes in the open
set. Although A* can still exhibit exponential behavior in the worst case (for
example, when no valid path exists or the heuristic offers no useful guidance),
it generally expands far fewer nodes than Dijkstra’s Algorithm thanks to the
heuristic directing the search.

## Features
- Animated terminal visualization
- Euclidean or Manhattan or Chebyshev Distance Heuristic
- Edge counter
- Custom or prebuilt graphs
- Custom start and goal nodes
- Modular and integratable methods

## Live Print Example
![A* Pathfinding Algorithm](/assets/A*GifExample.gif)

## How to Build

This project uses CMake, and there are no external dependencies. 

To build:

```bash
    mkdir build
    cd build
    cmake ..
    make