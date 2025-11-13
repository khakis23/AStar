#include "aStar.h"
#include "PreDefinedGrids.h"


/************************/
/***** CONSTRUCTORS *****/
/************************/

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


/******************/
/***** PUBLIC *****/
/******************/

void AStar::printMap(const std::unordered_set<Vec2, Vec2Hash>* open_set) const {
    using namespace color;
    clearScreen();

    for (int y = 0; y < grid_size.x; y++) {
        for (int x = 0; x < grid_size.y; x++) {
            if (grid[y][x])
                std::cout << BLACK << "██";
            else if (path.contains(Vec2{x, y}))
                std::cout << GREEN << "██";
            else if (open_set && open_set->contains(Vec2{x, y}))   // only prints if open_set is not null
                std::cout << YELLOW << "██";
            else
                std::cout << WHITE << "██";
            std::cout << RESET;
        }
        std::cout << std::endl;
    }
}

void AStar::setHeuristic(const Heuristic h) {
    h_eq = h;
}

std::unordered_set<Vec2, Vec2Hash> AStar::find(const Vec2 &start, const Vec2 &end, bool live_print) {
    // safety check for coordinates
    if (!validVec(start)) {
        std::cerr << "Invalid starting coordinate." << std::endl;
        return {};
    }
    if (!validVec(end)) {
        std::cerr << "Invalid ending coordinate." << std::endl;
        return {};
    }

    // setup
    std::priority_queue<Node*, std::vector<Node*>, CompareF> open_q;   // min heap
    std::unordered_set<Vec2, Vec2Hash> open_set;   // keep track of what's already in priority queue
    std::unordered_set<Vec2, Vec2Hash> closed;   // everything that's already been evaluated
    steps = 0;

    // first node
    Node start_node = {0, 0, 0,
        start,
        nullptr
    };
    start_node.h = start_node.f = getHeuristic(start, end);
    pool.push_back(start_node);
    open_q.push(&pool.back());
    open_set.insert(start);

    // main loop
    while (!open_q.empty()) {
        Node* cur = open_q.top();
        open_q.pop();
        steps++;

        // print live ("animated")
        if (live_print) {
            path = reconstructPath(cur);
            printMap(&open_set);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }

        // got to the end
        if (cur->pos == end) {
            std::cout << color::GREEN << "Found path in " << steps << " steps!" << color::RESET << std::endl;
            path = reconstructPath(cur);
            return path;
        }

        // move to closed list
        closed.insert(cur->pos);
        open_set.erase(cur->pos);

        for (auto neighbor : getNeighbors(cur->pos)) {
            // check collision
            if (neighbor.x < 0 || neighbor.x >= grid_size.x || neighbor.y < 0 || neighbor.y >= grid_size.y) //...with wall
                continue;
            if (grid[neighbor.y][neighbor.x])   //...with obstacle
                continue;

            // calculate this neighbor's costs
            const auto h_cost = getHeuristic(neighbor, end);
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
    // all possible spaces have been evaluated
    std::cout << color::RED << "No path was found. Steps: " << steps << color::RESET << std::endl;
    return {};
}


/*******************/
/***** PRIVATE *****/
/*******************/

unsigned int AStar::getHeuristic(Vec2 cur, Vec2 des) const {   // Manhattan h(n)
    if (h_eq == MANHATTAN)
        return (std::abs(cur.x - des.x) + std::abs(cur.y - des.y)) * 10;
    if (h_eq == EUCLIDEAN)
        return std::sqrt(std::pow((cur.x-des.x), 2) + std::pow((cur.x-des.x), 2));
    std::cerr << "Invalid heuristic." << std::endl;
    return -1;
}

unsigned int AStar::moveCost(Vec2 a, Vec2 b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) == 2 ? std::sqrt(2.0) * 10 : 10;
}

std::unordered_set<Vec2, Vec2Hash> AStar::reconstructPath(const Node* node) const {
    std::unordered_set<Vec2, Vec2Hash> p;
    while (node) {
        // std::cout << node->pos.x << ", " << node->pos.y << std::endl;
        p.insert(node->pos);
        node = node->parent;
    }
    return p;
}

bool AStar::validVec(const Vec2& v) const {
    if (v.x == grid_size.x || v.y == grid_size.y || v.x < 0 || v.y <0)
        return false;
    if (grid[v.y][v.x])
        return false;
    return true;
}

unsigned int AStar::getSteps() const {
    return steps;
}


/*******************/
/***** HELPERS *****/
/*******************/

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
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
