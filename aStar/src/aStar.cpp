#include "aStar.h"


AStar::AStar() {
    path = {};
}

void AStar::printMap() const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j])
                std::cout << "▒▒";
            else if (path.contains(Vec2{i, j}))
                std::cout << "██";
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
    }
}

std::unordered_set<Vec2, Vec2Hash> AStar::reconstructPath(const Node* node) const {
    std::unordered_set<Vec2, Vec2Hash> path;
    while (node) {
        std::cout << node->pos.x << ", " << node->pos.y << std::endl;
        path.insert(node->pos);
        node = node->parent;
    }
    return path;
}

unsigned int AStar::getHMan(Vec2 cur, Vec2 des) const {   // Manhattan h(n)
    return (std::abs(cur.x - des.x) + std::abs(cur.y - des.y)) * 10;
}

unsigned int AStar::moveCost(Vec2 a, Vec2 b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) == 2 ? std::sqrt(2.0) * 10 : 10;
}

std::vector<Vec2> AStar::getNeighbors(Vec2 pos) const {
    return {
            {pos.x + 1, pos.y - 1},
            {pos.x + 1, pos.y},
            {pos.x + 1, pos.y + 1},
            {pos.x - 1, pos.y - 1},
            {pos.x - 1, pos.y},
            {pos.x - 1, pos.y + 1},
            {pos.x, pos.y - 1},
            {pos.x, pos.y + 1}};
}

void AStar::find(const Vec2 &start, Vec2 end) {
    std::priority_queue<Node*, std::vector<Node*>, CompareF> open_q;   // min heap
    std::unordered_set<Vec2, Vec2Hash> open_set;
    std::unordered_set<Vec2, Vec2Hash> closed;

    Node start_node = {
        0,
        0,
        0,
        start,
        nullptr
    };
    start_node.h = start_node.f = getHMan(start, end);
    pool.push_back(start_node);
    open_q.push(&pool.back());
    open_set.insert(start);

    while (!open_q.empty()) {
        Node* cur = open_q.top();
        open_q.pop();
        // pool.push_back(*cur);

        // TODO check stale entry?

        // got to the end
        if (cur->pos == end) {
            std::cout << "Found path!" << std::endl;
            path = reconstructPath(cur);
            return;
        }

        // move to closed list
        closed.insert(cur->pos);
        open_set.erase(cur->pos);

        for (auto neighbor : getNeighbors(cur->pos)) {
            if (neighbor.x < 0 || neighbor.x >= 10 || neighbor.y < 0 || neighbor.y >= 10)
                continue;
            if (grid[neighbor.x][neighbor.y])
                continue;

            auto h_cost = getHMan(neighbor, end);
            auto g_cost = cur->g + moveCost(cur->pos, neighbor);
            auto f_cost = g_cost + h_cost;

            if (!open_set.contains(neighbor) && !closed.contains(neighbor)) {
                open_set.insert(neighbor);
                pool.push_back({g_cost, h_cost, f_cost, neighbor, cur});
                open_q.push(&pool.back());
            }
        }
    }
}