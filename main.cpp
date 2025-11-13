#include "aStar.h"


/*
 * TODO:
 *  - test/presentation program
 *  - Corner toggle??
 */


int main() {
    AStar astar('a');
    astar.printMap();
    // astar.setHeuristic(EUCLIDEAN);
    astar.find({1, 1}, {8, 8}, true);
    // astar.printMap();

    return 0;
}