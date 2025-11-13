#include "aStar.h"


/*
 * TODO:
 *  - test/presentation program
 *  - Corner toggle??
 *  - check stalemate condition
 */


int main() {
    AStar astar('f');
    astar.printMap();
    astar.setHeuristic(EUCLIDEAN);
    astar.find({1, 1}, {25, 27}, true);
    // astar.printMap();

    return 0;
}