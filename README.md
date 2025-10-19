<h1 align="center" font-size="200em"><b> Inteligência Artificial - Busca (não informada e informada) e 8 Rainhas (Hill Climbing)</b></h1>

<div align = "center" >

[![requirement](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-informational)](https://code.visualstudio.com/docs/?dv=linux64_deb)
![g++](https://img.shields.io/badge/Compilacao-G++-orange)
![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue)
</div>

# Sumário

- [Objetivos](#Objetivos)
- [Problema apresentado](#Problema-apresentado)
- [Arquivos](#Arquivos)
- [Resolução do Problema](#Resolução-do-problema)
- [Conclusão](#Conclusão)
- [Compilação e Execução](#Compilação-e-Execução)
- [Contato](#Contato)

## Objetivos
 O objetivo é consolidar os conceitos de busca em espaço de estados aprendidos em sala de aula. 

Na aplicação de Busca informada e não informada, propos a pratica de busca em um labirinto, tendo assim a comparação entre os dois conceitos.

E na 8 Rainhas, resolver o problema por meio da Hill Climbing( subida de encosta), e comparar o resultado pelo menos duas variações.

## Problema apresentado
### Busca
Implementar e comparar dois algoritmos de busca não informada (ex.: BFS, DFS, Custo Uniforme) e dois algoritmos de busca informada (Gulosa e A*) aplicados ao problema do labirinto.

Arquivo texto com grade retangular; caracteres permitidos: S (início), G (objetivo), # (parede), . (livre). Uma linha por linha do grid. Assim como é representado logo abaixo.

    S....
    .###.
    ..#..
    .###.
    ....G

### 8 Rainhas
Resolver o problema das 8 Rainhas por Hill Climbing (subida de encosta), comparando pelo menos duas variacões:
- (i) movimentos laterais permitidos com limite,
- (ii) reinícios aleatórios(Random-Restart). 

Opcional: Simulated Annealing para contraste.

## Arquivos

    INTELIGENCIA_ARTIFICIAL_BUSCA_E_8_RAINHAS
    ├── Busca (não informada e informada)
    │    ├── informada
    |    |        ├── Busca Gulosa
    |    |        |   ├── data
    |    |        |   │   └── labirinto.txt
    |    |        │   └── src
    |    |        │       ├── BG.hpp
    |    |        │       └── main.cpp
    |    |        └── Ma
    │    └── não informada 
    │           ├── BFS
    │           |    ├── data
    |           |    │   └── labirinto.txt
    |           |    └── src
    |           |         ├── BFS.hpp
    |           |         └── main.cpp
    |           └── Ma


    ├── imgs
    ├── .gitignore
    └── README.md

**../../../data/labiritmo.txt:** Arquivo que fica o layout do mapa do labirinto.

**../../../src/main.cpp:** Responsavel pela leitura do mapa e pela socicitação da chamada das funçãões da busca. E tambem é responsavel que mostrar se a operação ocorreu bem.

**../informada/Busca Gulosa/src/BG.hpp:** Onde é criado das todas as funções e structs da busca gulosa que serão executada executadas no decorrer do algoritmo.

**../não informada/BFS/src/BFS.hpp:** Onde é criado das todas as funções e structs da busca em largura que serão executada executadas no decorrer do algoritmo.

## Resolução do Problema

### Busca no Labirinto





## Conclusão 

