#ifndef BG_HPP
#define BG_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <set>
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
    int path_cost;
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


// Busca Gulosa 
std::vector<std::string> greedy_best_first_search(const Problem &problem) {
    size_t max_memory = 0;
    int nodes_generated = 0;
    int nodes_expanded = 0;

    Node* root = new Node{problem.start, nullptr, "", 0};

    auto h_manhattan = [](const State& a, const State& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    };


    // Fila de prioridade (menor h(n) tem maior prioridade)
    auto cmp = [](const std::pair<int, Node*>& a, const std::pair<int, Node*>& b) {
        return a.first > b.first;
    };
    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, decltype(cmp)> frontier(cmp);

    frontier.push({h_manhattan(root->state, problem.goal), root});
    std::set<State> explored;

    while (!frontier.empty()) {
        Node* node = frontier.top().second;
        frontier.pop();
        nodes_expanded++;

        // Teste de objetivo
        if (problem.goal_test(node->state)) {
            max_memory = std::max(max_memory, frontier.size() + explored.size());
            std::cout << "Busca Gulosa concluída com sucesso!\n";
            std::cout << "Nós gerados: " << nodes_generated << "\n";
            std::cout << "Nós expandidos: " << nodes_expanded << "\n";
            std::cout << "Máxima memória usada: " << max_memory << " nós\n";
            return solution(node);
        }

        explored.insert(node->state);

        // Expande os vizinhos
        for (auto &action_pair : problem.actions(node->state)) {
            std::string action = action_pair.first;
            State child_state = action_pair.second;

            if (explored.count(child_state)) continue;

            Node* child = new Node{child_state, node, action, node->path_cost + 1};
            nodes_generated++;

            int h = h_manhattan(child_state, problem.goal);
            frontier.push({h, child});
        }

        max_memory = std::max(max_memory, frontier.size() + explored.size());
    }

    std::cout << "Falha: nenhum caminho encontrado.\n";
    return {};
}

#endif
