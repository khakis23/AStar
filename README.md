# A* Pathfinding Algorithm
### Author: Tyler Black
A fast lightweight implementation of the A* pathfinding algorithm in C++,
designed to be easily integrated into larger applications, with optional
terminal visualization.

## How A* Works
The A* search algorithm is a widely used pathfinding algorithm. On a high
level, the algorithm works by finding the shortest path between two points
on a weighted graph. However, there are several sections of the algorithm
that allow A* to be a highly efficient pathfinding algorithm. 

The basics of A* are straightforward but important to understand. A weighted graph
must have nodes connected by edges, with the edges having a numerical weight/cost.
In the simplest of cases, like the one used in this project, the cost of each
edge is 1. This means moving from one node to a neighboring node always costs 1,
no matter the direction.

To break down A*, it can be written as a simple function: 
$$f(n)=g(n)+h(n)$$

$g(n)$ is the sum of each edge's cost to get to that node. If the algorithm
moves 4 spots in this project's 1-edge-cost graph, then its g-score will be 4.
The g-cost comes directly from Dijkstra's Algorithm, which can be used to
find the shortest path between two nodes. Dijkstra's Algorithm requires
evaluation of all nodes, which does not scale well for large graphs.

$h(n)$ is the heuristic value of each node, and it is what makes A* different
from Dijkstra's Algorithm. The heuristic value is the estimated distance from
the current node to the goal node. It can be calculated using different expressions,
but the most common are Manhattan Distance and Euclidean Distance. 

$f(n)$ is the total cost of a node from the start node to the goal node,
unlike Dijkstra's Algorithm which only considers the cost from the start node
to the current node. Having a total cost allows the algorithm to make a 
simple comparison. If one node has a lower f-score than another, then it is
considered to be a better path, and the higher cost node does not need to be
evaluated. This mechanism enables A* to discard large portions of the graph, 
mitigating the exponential growth of Dijkstra's Algorithm.


## Features
- Animated terminal visualization
- Euclidean or Manhattan Distance Heuristic
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