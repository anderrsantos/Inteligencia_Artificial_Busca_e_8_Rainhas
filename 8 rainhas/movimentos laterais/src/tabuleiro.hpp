#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>


struct Movimento{
    int nova_linha;
    int coluna;
};


std::vector<int> initial_board(int n){
    std::vector<int> board(n);
    srand(time(nullptr));

    for(int i = 0; i < n; ++i){
        board[i] = rand() % n ;
    }
    return board;
}

int conflicts(const std::vector<int>& board) {
    int n = board.size();
    int conflict_count = 0;

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(board[i] == board[j] || abs(board[i] - board[j]) == abs(i - j)) {
                conflict_count++;
            }
        }
    }
    return conflict_count;
}

std::vector<Movimento> neighbors(const std::vector<int>& board) {
    std::vector<Movimento> moves;
    int n = board.size();

    for(int col = 0; col < n; ++col) {
        while(true) {
            int new_row = rand() % n;
            if(new_row != board[col]) {
                Movimento move;
                move.nova_linha = new_row;
                move.coluna = col;
                moves.push_back(move);
                break;
            }
        }
    }

    return moves;
}

std::vector<int> apply_board(const std::vector<int>& board, const Movimento& move) {
    std::vector<int> new_board = board;
    new_board[move.coluna] = move.nova_linha;
    return new_board;
}


#endif