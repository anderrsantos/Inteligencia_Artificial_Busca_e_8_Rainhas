#ifndef COMPARADOR_ALGORITMOS_HPP
#define COMPARADOR_ALGORITMOS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>

// Estruturas básicas compartilhadas
struct State { 
    int x, y;
    State(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const State& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const State& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

struct Node {
    State state;
    Node* parent;        
    std::string action;
    int path_cost; 
    
    Node(State s, Node* p = nullptr, std::string a = "", int cost = 0) 
        : state(s), parent(p), action(a), path_cost(cost) {}
};

struct Problem {
    State initial_state;  
    State goal_state;     
    std::vector<std::vector<int>> map; // 0 = livre, 1 = obstáculo

    bool goal_test(const State& state) const {
        return state == goal_state;
    }

    std::vector<std::pair<std::string, State>> actions(const State &s) const {
        std::vector<std::pair<std::string, State>> results;
        std::vector<std::pair<std::string, std::pair<int,int>>> moves = {
            {"NORTE", {0, -1}}, {"SUL", {0, 1}}, {"OESTE", {-1, 0}}, {"LESTE", {1, 0}}
        };

        for (auto &m : moves) {
            int nx = s.x + m.second.first;
            int ny = s.y + m.second.second;
            if (nx >= 0 && ny >= 0 && ny < map.size() && nx < map[0].size() && map[ny][nx] == 0) {
                results.push_back({m.first, {nx, ny}});
            }
        }
        return results;
    }
};

struct AlgorithmResults {
    std::string name;
    std::vector<std::string> path;
    double execution_time;
    size_t max_memory;
    int nodes_generated;
    int nodes_expanded;
    int path_cost;
    bool found_solution;
    bool is_optimal;
};

// Função auxiliar para reconstruir caminho
std::vector<std::string> solution(Node* node) {
    std::vector<std::string> path;
    while (node->parent != nullptr) { 
        path.push_back(node->action);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// =================================================
// Busca Não Informada
// =================================================
// Implementação BFS
std::vector<std::string> breadth_first_search(const Problem &problem, AlgorithmResults &results) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    Node* root = new Node(problem.initial_state);
    nodes_generated++;

    if (problem.goal_test(root->state)) {
        results.path = {};
        results.found_solution = true;
        results.path_cost = 0;
        return {};
    }

    std::queue<Node*> frontier; 
    frontier.push(root);
    std::set<State> explored;

    while (!frontier.empty()) {
        Node* node = frontier.front();
        frontier.pop();
        nodes_expanded++;

        explored.insert(node->state);

        for (auto &action_pair : problem.actions(node->state)) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            bool in_frontier = false;
            std::queue<Node*> temp = frontier;
            while (!temp.empty()) {
                if (temp.front()->state == child_state) {
                    in_frontier = true;
                    break;
                }
                temp.pop();
            }

            if (explored.count(child_state) == 0 && !in_frontier) {
                Node* child = new Node(child_state, node, action, node->path_cost + 1);
                nodes_generated++;

                if (problem.goal_test(child->state)) {
                    max_memory = std::max(max_memory, frontier.size() + explored.size());
                    
                    auto end_time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsed = end_time - start_time;
                    
                    results.execution_time = elapsed.count();
                    results.max_memory = max_memory;
                    results.nodes_generated = nodes_generated;
                    results.nodes_expanded = nodes_expanded;
                    results.path_cost = child->path_cost;
                    results.found_solution = true;
                    results.is_optimal = true;
                    results.path = solution(child);
                    
                    return results.path;
                }
                frontier.push(child);
            }
        }
        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    results.execution_time = elapsed.count();
    results.max_memory = max_memory;
    results.nodes_generated = nodes_generated;
    results.nodes_expanded = nodes_expanded;
    results.found_solution = false;
    results.is_optimal = false;
    
    return {};
}

// Implementação DFS
std::vector<std::string> depth_first_search(const Problem &problem, AlgorithmResults &results) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    Node* root = new Node(problem.initial_state);
    nodes_generated++;

    if (problem.goal_test(root->state)) {
        results.path = {};
        results.found_solution = true;
        results.path_cost = 0;
        return {};
    }

    std::stack<Node*> frontier; 
    frontier.push(root);
    std::set<State> explored;

    while (!frontier.empty()) {
        Node* node = frontier.top();
        frontier.pop();
        nodes_expanded++;

        explored.insert(node->state);

        auto actions = problem.actions(node->state);
        std::reverse(actions.begin(), actions.end());
        
        for (auto &action_pair : actions) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            bool in_frontier = false;
            std::stack<Node*> temp = frontier;
            while (!temp.empty()) {
                if (temp.top()->state == child_state) {
                    in_frontier = true;
                    break;
                }
                temp.pop();
            }

            if (explored.count(child_state) == 0 && !in_frontier) {
                Node* child = new Node(child_state, node, action, node->path_cost + 1);
                nodes_generated++;

                if (problem.goal_test(child->state)) {
                    max_memory = std::max(max_memory, frontier.size() + explored.size());
                    
                    auto end_time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsed = end_time - start_time;
                    
                    results.execution_time = elapsed.count();
                    results.max_memory = max_memory;
                    results.nodes_generated = nodes_generated;
                    results.nodes_expanded = nodes_expanded;
                    results.path_cost = child->path_cost;
                    results.found_solution = true;
                    results.is_optimal = false; // DFS não garante otimalidade
                    results.path = solution(child);
                    
                    return results.path;
                }
                frontier.push(child);
            }
        }
        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    results.execution_time = elapsed.count();
    results.max_memory = max_memory;
    results.nodes_generated = nodes_generated;
    results.nodes_expanded = nodes_expanded;
    results.found_solution = false;
    results.is_optimal = false;
    
    return {};
}

// =================================================
// =================================================
// Busca Informada
// =================================================
int euclidean_distance(const State& a, const State& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

// Algoritmo de Busca Gulosa com heurística Euclidiana
std::vector<std::string> greedy_search_euclidiana(const Problem &problem, AlgorithmResults &results) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    Node* root = new Node(problem.initial_state);
    nodes_generated++;

    auto cmp = [](const std::pair<double, Node*>& a, const std::pair<double, Node*>& b) {
        return a.first > b.first; // menor heurística = maior prioridade
    };
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, decltype(cmp)> frontier(cmp);

    auto euclidean_distance = [](const State& a, const State& b) {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    };

    frontier.push({euclidean_distance(root->state, problem.goal_state), root});
    std::set<State> explored;

    while (!frontier.empty()) {
        Node* node = frontier.top().second;
        frontier.pop();
        nodes_expanded++;

        if (problem.goal_test(node->state)) {
            max_memory = std::max(max_memory, frontier.size() + explored.size());
            
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end_time - start_time;
            
            results.execution_time = elapsed.count();
            results.max_memory = max_memory;
            results.nodes_generated = nodes_generated;
            results.nodes_expanded = nodes_expanded;
            results.path_cost = node->path_cost;
            results.found_solution = true;
            results.is_optimal = false; // Busca Gulosa não é ótima
            results.path = solution(node);
            
            return results.path;
        }

        explored.insert(node->state);

        for (auto &action_pair : problem.actions(node->state)) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            if (explored.count(child_state)) continue;

            Node* child = new Node(child_state, node, action, node->path_cost + 1);
            nodes_generated++;

            double h = euclidean_distance(child_state, problem.goal_state);
            frontier.push({h, child});
        }

        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    results.execution_time = elapsed.count();
    results.max_memory = max_memory;
    results.nodes_generated = nodes_generated;
    results.nodes_expanded = nodes_expanded;
    results.found_solution = false;
    results.is_optimal = false;
    
    return {};
}

// Algoritmo A* com heurística Euclidiana
std::vector<std::string> a_star_search_euclidiana(const Problem &problem, AlgorithmResults &results) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    struct NodeWithCost {
        Node* node;
        double f_cost;
        double h_cost;
        NodeWithCost(Node* n, double f, double h) : node(n), f_cost(f), h_cost(h) {}
    };

    auto cmp = [](const NodeWithCost& a, const NodeWithCost& b) {
        if (a.f_cost != b.f_cost) return a.f_cost > b.f_cost;
        return a.h_cost > b.h_cost;
    };

    auto euclidean_distance = [](const State& a, const State& b) {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    };

    double h_start = euclidean_distance(problem.initial_state, problem.goal_state);
    Node* root = new Node(problem.initial_state);
    nodes_generated++;

    std::priority_queue<NodeWithCost, std::vector<NodeWithCost>, decltype(cmp)> frontier(cmp);
    frontier.push(NodeWithCost(root, h_start, h_start));

    std::map<State, double> frontier_costs;
    std::set<State> explored;
    frontier_costs[root->state] = root->path_cost;

    while (!frontier.empty()) {
        Node* node = frontier.top().node;
        frontier.pop();
        nodes_expanded++;

        if (problem.goal_test(node->state)) {
            max_memory = std::max(max_memory, frontier.size() + explored.size());
            
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end_time - start_time;
            
            results.execution_time = elapsed.count();
            results.max_memory = max_memory;
            results.nodes_generated = nodes_generated;
            results.nodes_expanded = nodes_expanded;
            results.path_cost = node->path_cost;
            results.found_solution = true;
            results.is_optimal = true; // A* é ótimo
            results.path = solution(node);
            
            return results.path;
        }

        explored.insert(node->state);
        frontier_costs.erase(node->state);

        for (auto &action_pair : problem.actions(node->state)) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            if (explored.count(child_state)) continue;

            double child_g = node->path_cost + 1;
            double child_h = euclidean_distance(child_state, problem.goal_state);

            if (frontier_costs.find(child_state) != frontier_costs.end()) {
                if (frontier_costs[child_state] <= child_g) continue;
            }

            Node* child = new Node(child_state, node, action, child_g);
            nodes_generated++;

            frontier.push(NodeWithCost(child, child_g + child_h, child_h));
            frontier_costs[child_state] = child_g;
        }

        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    results.execution_time = elapsed.count();
    results.max_memory = max_memory;
    results.nodes_generated = nodes_generated;
    results.nodes_expanded = nodes_expanded;
    results.found_solution = false;
    results.is_optimal = false;
    
    return {};
}

// =================================================
// Heurística Manhattan
int manhattan_distance(const State& a, const State& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Implementação Busca Gulosa (com distância Manhattan)
std::vector<std::string> greedy_search_manhattan(const Problem &problem, AlgorithmResults &results) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    Node* root = new Node(problem.initial_state);
    nodes_generated++;

    auto cmp = [&problem](const std::pair<int, Node*>& a, const std::pair<int, Node*>& b) {
        return a.first > b.first;
    };
    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, decltype(cmp)> frontier(cmp);

    frontier.push({manhattan_distance(root->state, problem.goal_state), root});
    std::set<State> explored;

    while (!frontier.empty()) {
        Node* node = frontier.top().second;
        frontier.pop();
        nodes_expanded++;

        if (problem.goal_test(node->state)) {
            max_memory = std::max(max_memory, frontier.size() + explored.size());
            
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end_time - start_time;
            
            results.execution_time = elapsed.count();
            results.max_memory = max_memory;
            results.nodes_generated = nodes_generated;
            results.nodes_expanded = nodes_expanded;
            results.path_cost = node->path_cost;
            results.found_solution = true;
            results.is_optimal = false; // Gulosa não é ótima
            results.path = solution(node);
            
            return results.path;
        }

        explored.insert(node->state);

        for (auto &action_pair : problem.actions(node->state)) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            if (explored.count(child_state)) continue;

            Node* child = new Node(child_state, node, action, node->path_cost + 1);
            nodes_generated++;

            int h = manhattan_distance(child_state, problem.goal_state);
            frontier.push({h, child});
        }

        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    results.execution_time = elapsed.count();
    results.max_memory = max_memory;
    results.nodes_generated = nodes_generated;
    results.nodes_expanded = nodes_expanded;
    results.found_solution = false;
    results.is_optimal = false;
    
    return {};
}

// Implementação A* com heurística Manhattan
std::vector<std::string> a_star_search_manhattan(const Problem &problem, AlgorithmResults &results) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    struct NodeWithCost {
        Node* node;
        int f_cost;
        int h_cost;
        
        NodeWithCost(Node* n, int f, int h) : node(n), f_cost(f), h_cost(h) {}
    };

    auto cmp = [](const NodeWithCost& a, const NodeWithCost& b) {
        if (a.f_cost != b.f_cost) return a.f_cost > b.f_cost;
        return a.h_cost > b.h_cost;
    };

    int h_start = manhattan_distance(problem.initial_state, problem.goal_state);
    Node* root = new Node(problem.initial_state);
    nodes_generated++;

    std::priority_queue<NodeWithCost, std::vector<NodeWithCost>, decltype(cmp)> frontier(cmp);
    frontier.push(NodeWithCost(root, h_start, h_start));

    std::map<State, int> frontier_costs;
    std::set<State> explored;
    frontier_costs[root->state] = root->path_cost;

    while (!frontier.empty()) {
        Node* node = frontier.top().node;
        frontier.pop();
        nodes_expanded++;

        if (problem.goal_test(node->state)) {
            max_memory = std::max(max_memory, frontier.size() + explored.size());
            
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end_time - start_time;
            
            results.execution_time = elapsed.count();
            results.max_memory = max_memory;
            results.nodes_generated = nodes_generated;
            results.nodes_expanded = nodes_expanded;
            results.path_cost = node->path_cost;
            results.found_solution = true;
            results.is_optimal = true; // A* é ótimo
            results.path = solution(node);
            
            return results.path;
        }

        explored.insert(node->state);
        frontier_costs.erase(node->state);

        for (auto &action_pair : problem.actions(node->state)) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            if (explored.count(child_state)) continue;

            int child_g = node->path_cost + 1;
            int child_h = manhattan_distance(child_state, problem.goal_state);

            if (frontier_costs.find(child_state) != frontier_costs.end()) {
                if (frontier_costs[child_state] <= child_g) {
                    continue;
                }
            }

            Node* child = new Node(child_state, node, action, child_g);
            nodes_generated++;

            frontier.push(NodeWithCost(child, child_g + child_h, child_h));
            frontier_costs[child_state] = child_g;
        }

        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    results.execution_time = elapsed.count();
    results.max_memory = max_memory;
    results.nodes_generated = nodes_generated;
    results.nodes_expanded = nodes_expanded;
    results.found_solution = false;
    results.is_optimal = false;
    
    return {};
}

// =================================================
// =================================================


#endif // COMPARADOR_ALGORITMOS_CPP