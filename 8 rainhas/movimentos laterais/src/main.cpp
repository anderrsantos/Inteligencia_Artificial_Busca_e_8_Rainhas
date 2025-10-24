#include "mov.hpp"
#include <iostream>
#include <chrono>
#include <string>

#define tamanho_tabuleiro 8
#define limite_interacao 100
#define limite_reinicios 50

int main() {

    std::cout <<" =================================================================\n"; 
    std::cout <<" Resolvendo com Hill Climbing com movimentos laterais com máximo de " << std::to_string(limite_interacao)<<" interações.\n";
    int numero_iteracoes = 0;
    
    auto start1 = std::chrono::high_resolution_clock::now();
    std::vector<int> solved_board = hill_climbing_lateral(tamanho_tabuleiro, limite_interacao, &numero_iteracoes);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1);

    std::cout << "\nTabuleiro resolvido: ";
    for(auto pos : solved_board) {
        std::cout << pos << " ";
    }
    std::cout << "\nNumero de conflitos atual: " << conflicts(solved_board) << std::endl;
    std::cout << "Numero de iteracoes: " << numero_iteracoes << std::endl;
    std::cout << "Tempo de execucao: " << duration1.count() << " segundos" << std::endl;
    std::cout <<" =================================================================\n"; 

    std::cout << "Resolvendo com Hill Climbing com REINICIOS ALEATORIOS (Random-Restart), com máximo de "<< std::to_string(limite_interacao)<<" interações e " << std::to_string(limite_reinicios)<<" reinicios.\n";

    int numero_iteracoes2 = 0;
    int numero_reinicios = 0;

    auto start2 = std::chrono::high_resolution_clock::now();
    std::vector<int> solved_board_restart = hill_climbing_random_restart(tamanho_tabuleiro, limite_reinicios, limite_interacao, &numero_iteracoes2, &numero_reinicios);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::duration<double>>(end2 - start2);

    std::cout << "\nTabuleiro resolvido: ";
    for (auto pos : solved_board_restart)
        std::cout << pos << " ";

    std::cout << "\nNumero de conflitos atual: " << conflicts(solved_board_restart) << std::endl;
    std::cout << "Numero de iteracoes totais: " << numero_iteracoes2 << std::endl;
    std::cout << "Numero de reinicios: " << numero_reinicios << std::endl;
    std::cout << "Tempo de execucao: " << duration2.count() << " segundos" << std::endl;
    std::cout << "=================================================================\n";

    return 0;
}