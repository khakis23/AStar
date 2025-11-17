#include "aStar.h"


int main() {
    /*
     * Example of Usage
     */
    AStar astar('f');
    astar.printMap();   // show initial map without any pathfinding
    astar.setLivePrintSpeed(100);
    astar.setHeuristic(MANHATTAN);
    astar.find({1, 1}, {27, 27}, true);

    return 0;
}