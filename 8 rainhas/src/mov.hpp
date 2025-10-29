#ifndef MOV_HPP
#define MOV_HPP

#include "tabuleiro.hpp"
#include <algorithm>
#include <iostream>
#include <cstdlib> 
#include <climits> 

std::vector<int> hill_climbing_lateral(int tamanho_tabuleiro, int max_lateral, int *numero_iteracoes) {

    std::vector<int> current_board = initial_board(tamanho_tabuleiro);
    int current_conflicts = conflicts(current_board);
    int lateral_moves = 0;

    *numero_iteracoes = 0;

    while (true) {
        (*numero_iteracoes)++; 

        std::vector<Movimento> possible_moves = neighbors(current_board);
        if (possible_moves.empty()) break;

        std::vector<std::vector<int>> neighbor_boards;
        std::vector<int> neighbor_conflicts;

        for (const auto& move : possible_moves) {
            std::vector<int> new_board = apply_board(current_board, move);
            neighbor_boards.push_back(new_board);
            neighbor_conflicts.push_back(conflicts(new_board));
        }

        auto min_it = std::min_element(neighbor_conflicts.begin(), neighbor_conflicts.end());
        int min_conflicts = *min_it;
        std::size_t min_index = std::distance(neighbor_conflicts.begin(), min_it);
        std::vector<int> best_board = neighbor_boards[min_index];

        if (min_conflicts == current_conflicts) {
            if (++lateral_moves > max_lateral) break;  
            current_board = best_board;
        } else if (min_conflicts < current_conflicts) {
            current_board = best_board;
            current_conflicts = min_conflicts;
            lateral_moves = 0;  
        } else break;

        if (current_conflicts == 0) break; 
    }

    return current_board;
}

std::vector<int> hill_climbing_random(int tamanho_tabuleiro, int max_attempts, int *numero_iteracoes) {
    std::vector<int> current_board = initial_board(tamanho_tabuleiro);
    int current_conflicts = conflicts(current_board);

    *numero_iteracoes = 0; 

    for (int attempt = 0; attempt < max_attempts; ++attempt) {
        (*numero_iteracoes)++; 

        std::vector<Movimento> possible_moves = neighbors(current_board);
        if (possible_moves.empty()) break;

        std::vector<std::vector<int>> neighbor_boards;
        std::vector<int> neighbor_conflicts;

        for (const auto& move : possible_moves) {
            std::vector<int> new_board = apply_board(current_board, move);
            neighbor_boards.push_back(new_board);
            neighbor_conflicts.push_back(conflicts(new_board));
        }

        auto min_it = std::min_element(neighbor_conflicts.begin(), neighbor_conflicts.end());
        int min_conflicts = *min_it;
        std::size_t min_index = std::distance(neighbor_conflicts.begin(), min_it);
        std::vector<int> best_board = neighbor_boards[min_index];

        if (min_conflicts < current_conflicts) {
            current_board = best_board;
            current_conflicts = min_conflicts;
        } else {
            int random_index = rand() % possible_moves.size();
            current_board = apply_board(current_board, possible_moves[random_index]);
            current_conflicts = conflicts(current_board);
        }

        if (current_conflicts == 0) break;
    }

    return current_board;
}

std::vector<int> hill_climbing_random_restart(int tamanho_tabuleiro, int max_restarts, int max_attempts, int *numero_iteracoes, int *num_reinicios) {
    std::vector<int> best_board;
    int best_conflicts = INT_MAX;

    *numero_iteracoes = 0;
    *num_reinicios = 0;

    for (int restart = 0; restart < max_restarts; ++restart) {
        (*num_reinicios)++;

        int iter_local = 0;
        std::vector<int> solved_board = hill_climbing_random(tamanho_tabuleiro, max_attempts, &iter_local);

        (*numero_iteracoes) += iter_local;

        int current_conflicts = conflicts(solved_board);

        if (current_conflicts < best_conflicts) {
            best_conflicts = current_conflicts;
            best_board = solved_board;
        }

        if (best_conflicts == 0) break; 

    }

    return best_board;
}

#endif
