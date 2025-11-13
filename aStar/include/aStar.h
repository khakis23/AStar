#ifndef A__ASTAR_H
#define A__ASTAR_H

#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <thread>
#include "PreDefinedGrids.h"


/**************************/
/***** HELPER STRUCTS *****/
/**************************/

struct Vec2 {
    int x = 0;
    int y = 0;
    bool operator==(const Vec2 &other) const {
        return x == other.x && y == other.y;
    }
};

struct Node {
    unsigned int g;   // distance from start
    unsigned int h;   // estimation to finish
    unsigned int f;   // g + h
    Vec2 pos;
    Node* parent = nullptr;
};


// overload queue to handle our Nodes
struct CompareF {
    bool operator()(const Node* a, const Node* b) const {
        return a->f > b->f;
    }
};

// overload set for hashing pair
struct Vec2Hash {
    size_t operator()(const Vec2 &pos) const {
        return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
    }
};


// for getHeuristic
enum Heuristic {
    EUCLIDEAN,
    MANHATTAN,
};


// colors for console printing
namespace color {
    inline auto RESET = "\033[0m";
    inline auto BLACK = "\033[30m";
    inline auto WHITE = "\033[37m";
    inline auto YELLOW = "\033[33m";
    inline auto GREEN = "\033[32m";
    inline auto RED = "\033[31m";
}


// helper funcs
void clearScreen();   // for printMap()
std::vector<Vec2> getNeighbors(Vec2 pos);   // for find()


/******************************/
/***** A* CLASS INTERFACE *****/
/******************************/

/**
 * @class AStar
 * @brief Implements A* pathfinding over a 2D boolean grid.
 */
class AStar {
public:

    /**
     * @param predef Pre-defined map/grid from "PreDefinedGrids.h"
     */
    AStar(char predef = 'a');


    /**
     * @param map Custom map/grid. Map can be n x m.
     */
    AStar(const std::vector<std::vector<bool>> &map);


    /**
     * @brief Print map using path attribute.
     *
     * @param open_set (optional) pass in open_set* to see "attempted" path nodes.
     */
    void printMap(const std::unordered_set<Vec2, Vec2Hash>* open_set=nullptr) const;


    /**
     * @brief Set the heuristic equation use for path finding.
     *
    * @param h use EUCLIDEAN or MANHATTAN (default) equation
     */
    void setHeuristic(Heuristic h);


    /**
     * @brief Use A* algorithm to try to find the shortest path from one coordinate to another.
     *
     * @param start staring coordinate (x,y)
     * @param end ending coordinate (x,y)
     * @param live_print (optional) print each frame of the path finding, including "attempted" nodes
     *
     * @returns path
     */
    std::unordered_set<Vec2, Vec2Hash> find(const Vec2 &start, const Vec2 &end, bool live_print=false);

private:

    /*** A* Attributes ***/

    std::unordered_set<Vec2, Vec2Hash> path;
    std::deque<Node> pool;
    Vec2 grid_size;
    std::vector<std::vector<bool>> grid;
    Heuristic h_eq = MANHATTAN;
    unsigned int steps = 0;


    /*** A* Helper & Getter Methods ***/

    [[nodiscard]] unsigned int getHeuristic(Vec2 cur, Vec2 des) const;
    [[nodiscard]] unsigned int moveCost(Vec2 x, Vec2 y) const;
    [[nodiscard]] bool validVec(const Vec2& v) const;
    [[nodiscard]] unsigned int getSteps() const;


    /**
     * @brief Get the path from current node back to start node.
     *
     * @param node last/current node
     * @return path
     */
    std::unordered_set<Vec2, Vec2Hash> reconstructPath(const Node* node) const;
};


#endif //A__ASTAR_H