#include "mov.hpp"
#include <iostream>
#define tamanho_tabuleiro 8

int main() {
    std::vector<int> board = initial_board(tamanho_tabuleiro);

    std::cout << "Tabuleiro inicial: ";
    for(auto pos : board) {
        std::cout << pos << " ";
    }
    std::vector<int> solved_board = hill_climbing_lateral(board);
    std::cout << "\nTabuleiro resolvido: ";
    for(auto pos : solved_board) {
        std::cout << pos << " ";
    }
    std::cout << "\nNumero de conflitos: " << conflicts(solved_board) << std::endl;

 
    return 0;
}