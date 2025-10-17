#include "BFS.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <chrono>


std::string arquivo = "../../data/labirinto.txt";

// Lê o mapa do arquivo e inicializa os estados inicial e objetivo
void readMap(Problem &problem) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
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

int main() {
    Problem problem;
    readMap(problem);
 
    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "=========================================\n";

    breadth_first_search(problem);

    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Tempo de execução: " << elapsed.count() << " segundos" << std::endl;
    std::cout << "=========================================\n"<< std::endl;


    return 0;
}
