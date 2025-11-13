#include "aStar.h"


/*
 * TODO:
 *  1. Add Another heurstics equation
 *  2. Corner toggle?
 *  3. Organize this shit!
 *  4. Ipliment grid size
 *  5. show path that has been "tried"
 */


int main() {
    AStar astar('f');
    // astar.printMap();
    astar.find({0, 0}, {29, 29});
    astar.printMap();

    return 0;
}