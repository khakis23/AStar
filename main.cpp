#include "aStar.h"


/*
 * TODO:
 *  1. Vec2 coordinates are backwards cuz [row][col]
 *  2. Corner toggle?
 *  3. Organize this shit!
 *  4.
 */


int main() {
    AStar astar;
    astar.printMap();
    astar.find({1, 1}, {7, 4});
    astar.printMap();

    return 0;
}