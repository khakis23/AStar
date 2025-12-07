#ifndef A__EXAMPLE_H
#define A__EXAMPLE_H
#include <iostream>
#include <ostream>
#include <thread>
#include "aStar.h"
#include "PreDefinedGrids.h"


inline void wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


inline void wait() {
    char _;
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


inline void examplePrint() {
    int wait_time = 3000;

    clearScreen();
    std::cout << "Example 1 - Map A - Manhattan Distance" << std::endl;
    wait(wait_time);
    AStar astar('a');
    astar.printMap();
    astar.setHeuristic(MANHATTAN);
    astar.find({1, 1}, {8, 8}, true);

    wait();

    clearScreen();
    std::cout << "Example 2 - Map A - Euclidean Distance" << std::endl;
    wait(wait_time);
    AStar astar2('a');
    astar2.printMap();
    astar2.setHeuristic(EUCLIDEAN);
    astar2.find({1, 1}, {8, 8}, true);

    wait();

    clearScreen();
    std::cout << "Example 3 - Map C - Manhattan Distance" << std::endl;
    wait(wait_time);
    AStar astar3('c');
    astar3.setLivePrintSpeed(150);
    astar3.printMap();
    astar3.setHeuristic(MANHATTAN);
    astar3.find({9, 9}, {19, 19}, true);

    wait();

    clearScreen();
    std::cout << "Example 4 - Map C - Euclidean Distance" << std::endl;
    wait(wait_time);
    AStar astar4('c');
    astar4.setLivePrintSpeed(150);
    astar4.printMap();
    astar4.setHeuristic(EUCLIDEAN);
    astar4.find({9, 9}, {19, 19}, true);

    wait();

    clearScreen();
    std::cout << "Example 5 - Map F - Manhattan Distance" << std::endl;
    wait(wait_time);
    AStar astar5('f');
    astar5.setLivePrintSpeed(50);
    astar5.printMap();
    astar5.setHeuristic(MANHATTAN);
    astar5.find({1, 1}, {23, 32}, true);

    wait();

    clearScreen();
    std::cout << "Example 6 - Map F - Euclidean Distance" << std::endl;
    wait(wait_time);
    AStar astar6('f');
    astar6.setLivePrintSpeed(50);
    astar6.printMap();
    astar6.setHeuristic(EUCLIDEAN);
    astar6.find({1, 1}, {23, 32}, true);

    wait();

    clearScreen();
    std::cout << "Example 7 - Map E - Unsolvable" << std::endl;
    wait(wait_time);
    AStar astar7('e');
    astar7.setLivePrintSpeed(30);
    astar7.printMap();
    astar7.setHeuristic(MANHATTAN);
    astar7.find({0, 0}, {15, 15}, true);
}


#endif //A__EXAMPLE_H