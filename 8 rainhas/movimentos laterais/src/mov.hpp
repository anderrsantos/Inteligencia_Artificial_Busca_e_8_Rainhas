#ifndef MOV_HPP
#define MOV_HPP

#include "tabuleiro.hpp"
#include <algorithm>
 
std::vector<int> hill_climbing_lateral(const std::vector<int>& initial_board, int max_lateral = 1000) {
    std::vector<int> current_board = initial_board;
    int current_conflicts = conflicts(current_board);

    int lateral_moves = 0;

    while (true) {
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
        }
        
        else if (min_conflicts < current_conflicts) {
            current_board = best_board;
            current_conflicts = min_conflicts;
            lateral_moves = 0;  
        }
        else break; 
    }

    return current_board;
}


#endif