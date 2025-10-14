#ifndef BSF_HPP
#define BSF_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <utility>

// STRUCTS responsavel por armazenar os estados 
struct State{ 
    int x;
    int y;
    
    State(int x, int y) : x(x), y(y){}

    bool VerifyState(State state) const{
        return (x == state.x && y == state.y);
    }
};

// STRUCT responsavel por armazenar os nos
struct Node {
    State state;
    Node* child;
    std::string action;
    int path_cost; 
};

// STRUCT responsavel por armazenar o problema (o mapa)
struct Problem {
    State initial_state;  //ponto de partida
    State goat_state;     //ponto de chegada

    std::vector<std::vector<int>> map; //0 = livre, 1 = obstaculo

    bool goal_test(State state) const { // verificar se chegou no final
        return goat_state.VerifyState(state);
    }

    // Retorna ações possíveis a partir de um estado
    std::vector<std::pair<std::string, State>> actions(const State &s) const {
        std::vector<std::pair<std::string, State>> results;

        std::vector<std::pair<std::string, std::pair<int,int>>> moves = {
            {"UP", {0, -1}}, {"DOWN", {0, 1}}, {"LEFT", {-1, 0}}, {"RIGHT", {1, 0}}
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

int breadth_first_search(const Problem &problem);

#endif