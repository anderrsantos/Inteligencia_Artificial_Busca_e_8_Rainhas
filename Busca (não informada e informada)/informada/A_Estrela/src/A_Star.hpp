#ifndef A_STAR_HPP
#define A_STAR_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

struct State {
    int x, y;
    State(int x = 0, int y = 0) : x(x), y(y) {}

    bool VerifyState(const State& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const State& other) const {
        return (x == other.x) ? y < other.y : x < other.x;
    }
};

struct Node {
    State state;
    Node* parent;
    std::string action;
    int path_cost;    // g(n) - custo do caminho até este nó
    int heuristic;    // h(n) - estimativa heurística até o objetivo
    int total_cost;   // f(n) = g(n) + h(n)
    
    Node(State s, Node* p, std::string a, int g, int h) 
        : state(s), parent(p), action(a), path_cost(g), heuristic(h), total_cost(g + h) {}
};

struct Problem {
    State start; 
    State goal;
    std::vector<std::vector<int>> map; // 0 = livre, 1 = obstáculo

    bool goal_test(const State& s) const {
        return goal.VerifyState(s);
    }

    std::vector<std::pair<std::string, State>> actions(const State &s) const {
        std::vector<std::pair<std::string, State>> results;
        std::vector<std::pair<std::string, std::pair<int, int>>> moves = {
            {"NORTE", {0, -1}}, {"SUL", {0, 1}},
            {"OESTE", {-1, 0}}, {"LESTE", {1, 0}}
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

// Reconstrói caminho da solução
std::vector<std::string> solution(Node* node) {
    std::vector<std::string> path;
    while (node->parent != nullptr) {
        path.push_back(node->action);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// Heurística de Manhattan (admissível para este problema)
int manhattan_distance(const State& a, const State& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Algoritmo A*
std::vector<std::string> a_star_search(const Problem &problem) {
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    // Função de comparação para a fila de prioridade (menor f(n) tem maior prioridade)
    auto cmp = [](Node* a, Node* b) {
        if (a->total_cost != b->total_cost) {
            return a->total_cost > b->total_cost;
        }
        // Em caso de empate em f(n), priorizar menor h(n) (mais próximo do objetivo)
        return a->heuristic > b->heuristic;
    };

    int h_start = manhattan_distance(problem.start, problem.goal);
    Node* root = new Node(problem.start, nullptr, "", 0, h_start);
    nodes_generated++;

    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> frontier(cmp);
    frontier.push(root);

    // Mapas para controlar custos já visitados
    std::map<State, int> frontier_costs;  // Estado -> menor g(n) na fronteira
    std::set<State> explored;

    frontier_costs[root->state] = root->path_cost;

    while (!frontier.empty()) {
        Node* node = frontier.top();
        frontier.pop();
        nodes_expanded++;

        // Teste de objetivo
        if (problem.goal_test(node->state)) {
            max_memory = std::max(max_memory, frontier.size() + explored.size());
            std::cout << "A* concluído com sucesso!\n";
            std::cout << "Nós gerados: " << nodes_generated << "\n";
            std::cout << "Nós expandidos: " << nodes_expanded << "\n";
            std::cout << "Máxima memória usada: " << max_memory << " nós\n";
            std::cout << "Custo ótimo encontrado: " << node->path_cost << "\n";
            std::cout << "Caminho encontrado: ";
            
            auto path = solution(node);
            for (auto &action : path) {
                std::cout << action << " ";
            }
            std::cout << std::endl;
            
            return path;
        }

        explored.insert(node->state);
        frontier_costs.erase(node->state);

        // Expande os vizinhos
        for (auto &action_pair : problem.actions(node->state)) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            if (explored.count(child_state)) continue;

            int child_g = node->path_cost + 1;  // Custo unitário por movimento
            int child_h = manhattan_distance(child_state, problem.goal);

            // Verifica se já existe na fronteira com custo menor ou igual
            if (frontier_costs.find(child_state) != frontier_costs.end()) {
                if (frontier_costs[child_state] <= child_g) {
                    continue;  // Já temos um caminho melhor ou igual
                }
            }

            Node* child = new Node(child_state, node, action, child_g, child_h);
            nodes_generated++;

            frontier.push(child);
            frontier_costs[child_state] = child_g;
        }

        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }

    std::cout << "A* falhou: nenhum caminho encontrado.\n";
    std::cout << "Nós gerados: " << nodes_generated << "\n";
    std::cout << "Nós expandidos: " << nodes_expanded << "\n";
    std::cout << "Máxima memória usada: " << max_memory << " nós\n";
    return {};
}

#endif