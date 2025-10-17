#ifndef BFS_HPP
#define BFS_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

// Representa um estado (posição x,y)
struct State { 
    int x;
    int y;
    
    State(int x = 0, int y = 0) : x(x), y(y) {}

    bool VerifyState(const State& state) const {
        return (x == state.x && y == state.y);
    }

    bool operator<(const State& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Representa um nó na árvore de busca
struct Node {
    State state;
    Node* parent;        
    std::string action;
    int path_cost; 
};


// Representa o problema (mapa)
struct Problem {
    State initial_state;  // ponto de partida
    State goal_state;     // ponto de chegada

    std::vector<std::vector<int>> map; // 0 = livre, 1 = obstáculo

    bool goal_test(const State& state) const {
        return goal_state.VerifyState(state);
    }

    // Retorna ações possíveis a partir de um estado
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

// Reconstrói o caminho até a solução
std::vector<std::string> solution(Node* node) {
    std::vector<std::string> path;
    while (node->parent != nullptr) { 
        path.push_back(node->action);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// Busca em Largura (BFS)
std::vector<std::string> breadth_first_search(const Problem &problem) {
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    Node* root = new Node{problem.initial_state, nullptr, "", 0};

    if (problem.goal_test(root->state))
        return {};

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
                if (temp.front()->state.VerifyState(child_state)) {
                    in_frontier = true;
                    break;
                }
                temp.pop();
            }

            if (explored.count(child_state) == 0 && !in_frontier) {
                Node* child = new Node{child_state, node, action, node->path_cost + 1};
                nodes_generated++;

                // Verifica se o estado filho é o estado objetivo
                if (problem.goal_test(child->state)) {

                    max_memory = std::max(max_memory, frontier.size() + explored.size());
                    std::cout << "Busca em Largura (BFS) concluída." << std::endl;
                    std::cout << "Máxima memória utilizada: " << max_memory << " nós" << std::endl;
                    
                    std::cout << "Nós gerados: " << nodes_generated << std::endl;
                    std::cout << "Nós expandidos: " << nodes_expanded << std::endl;

                    std::cout << "Custo do caminho: " << child->path_cost << std::endl;
                    std::cout << "Caminho encontrado: ";

                    for (auto &a : solution(child)) std::cout << a << " ";
                        std::cout << std::endl;

                    return solution(child);
                }

                frontier.push(child);
            }
        }
    }

    std::cout << "Nenhum caminho encontrado." << std::endl;
    return {}; 
}

#endif
