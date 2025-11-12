//
// Created by Tyler Black on 11/11/25.
//

#ifndef A__ASTAR_H
#define A__ASTAR_H
#include <iostream>
#include <queue>
#include <unordered_set>

// blocks: ▓, ▒, ░


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
    Node* parent = nullptr;   // TODO remove
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

class AStar {
    std::unordered_set<Vec2, Vec2Hash> path;
    std::deque<Node> pool;
    bool grid[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,1,0,1,1,0,1},
        {1,0,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,1,0,1,0,1},
        {1,1,1,1,0,1,0,1,0,1},
        {1,0,0,1,0,0,0,1,0,1},
        {1,0,1,1,1,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}};
    // bool grid[10][10] = {
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0,0}
    // };

    [[nodiscard]] unsigned int getHMan(Vec2 cur, Vec2 des) const;
    [[nodiscard]] unsigned int moveCost(Vec2 x, Vec2 y) const;
    std::vector<Vec2> getNeighbors(Vec2 pos) const;
    std::unordered_set<Vec2, Vec2Hash> reconstructPath(const Node* node) const;
public:
    AStar();
    void printMap() const;
    void find(const Vec2 &start, Vec2 end);
};





#endif //A__ASTAR_H