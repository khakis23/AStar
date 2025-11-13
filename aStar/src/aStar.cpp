#include "aStar.h"
#include "PreDefinedGrids.h"


AStar::AStar(const std::vector<std::vector<bool>> &map) : path({}), grid(map){
    grid_size.x = grid[0].size();
    grid_size.y = grid.size();
}

AStar::AStar(char ch) : path({}){
    try {
        grid = getGrid(ch);
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return;
    }
    grid_size.x = grid[0].size();
    grid_size.y = grid.size();
}

void AStar::printMap() const {
    for (int i = 0; i < grid_size.x; i++) {
        for (int j = 0; j < grid_size.y; j++) {
            if (grid[j][i])
                std::cout << "▒▒";
            else if (path.contains(Vec2{j, i}))
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
        // std::cout << node->pos.x << ", " << node->pos.y << std::endl;
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

std::vector<Vec2> getNeighbors(Vec2 pos) {
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

void AStar::find(const Vec2 &start, const Vec2 &end) {
    // safety check for coordinates
    if (!validVec(start)) {
        std::cerr << "Invalid starting coordinate." << std::endl;
        return;
    }
    if (!validVec(end)) {
        std::cerr << "Invalid ending coordinate." << std::endl;
        return;
    }

    std::priority_queue<Node*, std::vector<Node*>, CompareF> open_q;   // min heap
    std::unordered_set<Vec2, Vec2Hash> open_set;   // keep track of what's already in priority queue
    std::unordered_set<Vec2, Vec2Hash> closed;   // everything thats already been evaluated

    // first node
    Node start_node = {0, 0, 0,
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

        // TODO check stalemate??

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
            // check collision
            if (neighbor.x < 0 || neighbor.x >= grid_size.x || neighbor.y < 0 || neighbor.y >= grid_size.y)   //...with wall
                continue;
            if (grid[neighbor.y][neighbor.x])   //...with obstacle
                continue;

            // calculate this neighbor's costs
            const auto h_cost = getHMan(neighbor, end);
            const auto g_cost = cur->g + moveCost(cur->pos, neighbor);
            const auto f_cost = g_cost + h_cost;

            // add to queue if neighbor is not in it already
            if (!open_set.contains(neighbor) && !closed.contains(neighbor)) {
                open_set.insert(neighbor);
                pool.push_back({g_cost, h_cost, f_cost, neighbor, cur});
                open_q.push(&pool.back());
            }
        }
    }
}


bool AStar::validVec(const Vec2& v) const {
    if (v.x == grid_size.x || v.y == grid_size.y || v.x < 0 || v.y <0)
        return false;
    if (grid[v.y][v.x])
        return false;
    return true;
}
