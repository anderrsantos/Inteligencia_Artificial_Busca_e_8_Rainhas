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

// Heurística Manhattan
int manhattan_distance(const State& a, const State& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Implementação Busca Gulosa
std::vector<std::string> greedy_search(const Problem &problem, AlgorithmResults &results) {
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

// Implementação A*
std::vector<std::string> a_star_search(const Problem &problem, AlgorithmResults &results) {
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

// Função para ler o mapa
void readMap(Problem &problem, const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue; 
        std::vector<int> row;

        for (int j = 0; j < (int)line.size(); ++j) {
            char ch = line[j];
            if (ch == ' ') continue;

            if (ch == 'S' || ch == 's') {
                problem.initial_state = {j, i};
                row.push_back(0);
            } else if (ch == 'G' || ch == 'g') {
                problem.goal_state = {j, i};
                row.push_back(0);
            } else if (ch == '#') {
                row.push_back(1);
            } else {
                row.push_back(0);
            }
        }
        problem.map.push_back(row);
        i++;
    }
    file.close();
}

void printResults(const std::vector<AlgorithmResults> &results) {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                    RESULTADOS COMPARATIVOS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    // Cabeçalho da tabela
    std::cout << std::left << std::setw(15) << "Algoritmo"
              << std::setw(12) << "Tempo (s)"
              << std::setw(10) << "Memória"
              << std::setw(12) << "Nós Ger."
              << std::setw(12) << "Nós Exp."
              << std::setw(8) << "Custo"
              << std::setw(10) << "Solução"
              << std::setw(8) << "Ótimo" << std::endl;
    
    std::cout << std::string(80, '-') << std::endl;

    for (const auto &result : results) {
        std::cout << std::left << std::setw(15) << result.name
                  << std::setw(12) << std::fixed << std::setprecision(6) << result.execution_time
                  << std::setw(10) << result.max_memory
                  << std::setw(12) << result.nodes_generated
                  << std::setw(12) << result.nodes_expanded
                  << std::setw(8) << (result.found_solution ? std::to_string(result.path_cost) : "N/A")
                  << std::setw(10) << (result.found_solution ? "SIM" : "NÃO")
                  << std::setw(8) << (result.is_optimal ? "SIM" : "NÃO") << std::endl;
    }

    std::cout << std::string(80, '=') << std::endl;
    
    // Análise comparativa
    std::cout << "\nANÁLISE COMPARATIVA:\n" << std::endl;
    
    // Encontrar algoritmos que encontraram solução
    std::vector<AlgorithmResults> successful;
    for (const auto &r : results) {
        if (r.found_solution) successful.push_back(r);
    }
    
    if (!successful.empty()) {
        // Melhor tempo
        auto fastest = *std::min_element(successful.begin(), successful.end(),
            [](const AlgorithmResults &a, const AlgorithmResults &b) {
                return a.execution_time < b.execution_time;
            });
        
        // Menor memória
        auto least_memory = *std::min_element(successful.begin(), successful.end(),
            [](const AlgorithmResults &a, const AlgorithmResults &b) {
                return a.max_memory < b.max_memory;
            });
            
        // Menor custo (ótimo)
        auto optimal = *std::min_element(successful.begin(), successful.end(),
            [](const AlgorithmResults &a, const AlgorithmResults &b) {
                return a.path_cost < b.path_cost;
            });

        std::cout << "• Algoritmo mais rápido: " << fastest.name 
                  << " (" << fastest.execution_time << "s)" << std::endl;
        std::cout << "• Algoritmo com menor uso de memória: " << least_memory.name 
                  << " (" << least_memory.max_memory << " nós)" << std::endl;
        std::cout << "• Algoritmo(s) ótimo(s): ";
        
        for (const auto &r : successful) {
            if (r.path_cost == optimal.path_cost) {
                std::cout << r.name << " ";
            }
        }
        std::cout << "(custo " << optimal.path_cost << ")" << std::endl;
    }
    
    std::cout << std::endl;
}

int main() {
    Problem problem;
    readMap(problem, "labirinto.txt");

    std::vector<AlgorithmResults> results;
    
    std::cout << "Executando comparação de algoritmos de busca no labirinto...\n" << std::endl;

    // BFS
    std::cout << "Executando BFS..." << std::endl;
    AlgorithmResults bfs_result;
    bfs_result.name = "BFS";
    breadth_first_search(problem, bfs_result);
    results.push_back(bfs_result);

    // DFS  
    std::cout << "Executando DFS..." << std::endl;
    AlgorithmResults dfs_result;
    dfs_result.name = "DFS";
    depth_first_search(problem, dfs_result);
    results.push_back(dfs_result);

    // Busca Gulosa
    std::cout << "Executando Busca Gulosa..." << std::endl;
    AlgorithmResults greedy_result;
    greedy_result.name = "Gulosa";
    greedy_search(problem, greedy_result);
    results.push_back(greedy_result);

    // A*
    std::cout << "Executando A*..." << std::endl;
    AlgorithmResults astar_result;
    astar_result.name = "A*";
    a_star_search(problem, astar_result);
    results.push_back(astar_result);

    // Imprimir resultados
    printResults(results);

    return 0;
}