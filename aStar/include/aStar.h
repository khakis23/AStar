#ifndef A__ASTAR_H
#define A__ASTAR_H

#include <iostream>
#include <queue>
#include <unordered_set>

// NOTE: blocks: ▓, ▒, ░


/***** HELPER STRUCTS *****/

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

// overload set for hasing pair
struct Vec2Hash {
    size_t operator()(const Vec2 &pos) const {
        return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
    }
};


/***** A* CLASS INTERFACE *****/

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
     * TODO
     */
    void printMap() const;

    /**
     * TODO
     * @param start
     * @param end
     */
    void find(const Vec2 &start, const Vec2 &end);

private:

    /*** A* Attributes ***/

    std::unordered_set<Vec2, Vec2Hash> path;
    std::deque<Node> pool;
    Vec2 grid_size;
    std::vector<std::vector<bool>> grid;
    bool validVec(const Vec2& v) const;

    /*** A* Helper Methods ***/

    [[nodiscard]] unsigned int getHMan(Vec2 cur, Vec2 des) const;
    [[nodiscard]] unsigned int moveCost(Vec2 x, Vec2 y) const;
    std::unordered_set<Vec2, Vec2Hash> reconstructPath(const Node* node) const;
};


#endif //A__ASTAR_H