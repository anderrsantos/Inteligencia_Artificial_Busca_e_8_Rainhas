#include "src_comparador/comparador_algoritmos.hpp"


void readMap(Problem &problem, const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
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

void printResults(const std::vector<AlgorithmResults> &results) {
    std::cout << "\n" << std::string(90, '=') << std::endl;
    std::cout << "                 COMPARATIVO DE ALGORITMOS DE BUSCA" << std::endl;
    std::cout << std::string(90, '=') << std::endl;

    // Cabeçalho
    std::cout << std::left
              << std::setw(18) << "Algoritmo"
              << std::setw(12) << "Tempo (s)"
              << std::setw(10) << "Memória"
              << std::setw(12) << "Nós Ger."
              << std::setw(12) << "Nós Exp."
              << std::setw(8)  << "Custo"
              << std::setw(10) << "Solução"
              << std::setw(8)  << "Ótimo" 
              << std::endl;

    std::cout << std::string(90, '-') << std::endl;

    for (const auto &r : results) {
        std::cout << std::left
                  << std::setw(18) << r.name
                  << std::setw(12) << std::fixed << std::setprecision(6) << r.execution_time
                  << std::setw(10) << r.max_memory
                  << std::setw(12) << r.nodes_generated
                  << std::setw(12) << r.nodes_expanded
                  << std::setw(8)  << (r.found_solution ? std::to_string(r.path_cost) : "N/A")
                  << std::setw(10) << (r.found_solution ? "SIM" : "NÃO")
                  << std::setw(8)  << (r.is_optimal ? "SIM" : "NÃO")
                  << std::endl;
    }

    std::cout << std::string(90, '=') << std::endl;

    // Análise comparativa final
    std::cout << "\nANÁLISE COMPARATIVA:\n" << std::endl;

    std::vector<AlgorithmResults> successful;
    for (const auto &r : results)
        if (r.found_solution) successful.push_back(r);

    if (successful.empty()) {
        std::cout << "Nenhum algoritmo encontrou solução." << std::endl;
        return;
    }

    // Melhor tempo
    auto fastest = *std::min_element(successful.begin(), successful.end(),
        [](const AlgorithmResults &a, const AlgorithmResults &b) {
            return a.execution_time < b.execution_time;
        });

    // Menor memória
    auto least_memory = *std::min_element(successful.begin(), successful.end(),
        [](const AlgorithmResults &a, const AlgorithmResults &b) {
            return a.max_memory < b.max_memory;
        });

    // Menor custo (ótimo)
    auto optimal = *std::min_element(successful.begin(), successful.end(),
        [](const AlgorithmResults &a, const AlgorithmResults &b) {
            return a.path_cost < b.path_cost;
        });

    std::cout << "• Mais rápido: " << fastest.name 
              << " (" << fastest.execution_time << " s)" << std::endl;

    std::cout << "• Menor uso de memória: " << least_memory.name 
              << " (" << least_memory.max_memory << " nós)" << std::endl;

    std::cout << "• Custo ótimo (menor caminho): " << optimal.path_cost 
              << " — obtido por ";
    for (const auto &r : successful)
        if (r.path_cost == optimal.path_cost)
            std::cout << r.name << " ";
    std::cout << std::endl;

    std::cout << "\n" << std::string(90, '=') << std::endl;
}

int main() {
    Problem problem;
    readMap(problem, "src_comparador/labirinto.txt");

    std::vector<AlgorithmResults> results;

    std::cout << "\nExecutando comparação de algoritmos de busca...\n" << std::endl;

    // ======= BFS =======
    std::cout << "Executando BFS..." << std::endl;
    AlgorithmResults bfs_result;
    bfs_result.name = "BFS";
    breadth_first_search(problem, bfs_result);
    results.push_back(bfs_result);

    // ======= DFS =======
    std::cout << "Executando DFS..." << std::endl;
    AlgorithmResults dfs_result;
    dfs_result.name = "DFS";
    depth_first_search(problem, dfs_result);
    results.push_back(dfs_result);

    // ======= Gulosa Manhattan =======
    std::cout << "Executando Busca Gulosa (Manhattan)..." << std::endl;
    AlgorithmResults greedy_manhattan;
    greedy_manhattan.name = "Gulosa-Manh";
    greedy_search_manhattan(problem, greedy_manhattan);
    results.push_back(greedy_manhattan);

    // ======= Gulosa Euclidiana =======
    std::cout << "Executando Busca Gulosa (Euclidiana)..." << std::endl;
    AlgorithmResults greedy_euclidiana;
    greedy_euclidiana.name = "Gulosa-Eucl";
    greedy_search_euclidiana(problem, greedy_euclidiana);
    results.push_back(greedy_euclidiana);

    // ======= A* Manhattan =======
    std::cout << "Executando A* (Manhattan)..." << std::endl;
    AlgorithmResults astar_manhattan;
    astar_manhattan.name = "A*-Manh";
    a_star_search_manhattan(problem, astar_manhattan);
    results.push_back(astar_manhattan);

    // ======= A* Euclidiana =======
    std::cout << "Executando A* (Euclidiana)..." << std::endl;
    AlgorithmResults astar_euclidiana;
    astar_euclidiana.name = "A*-Eucl";
    a_star_search_euclidiana(problem, astar_euclidiana);
    results.push_back(astar_euclidiana);

    // ======= Mostrar resultados =======
    printResults(results);

    return 0;
}
