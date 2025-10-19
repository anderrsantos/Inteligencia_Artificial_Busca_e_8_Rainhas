<h1 align="center" font-size="200em"><b> Inteligência Artificial - Busca (não informada e informada)</b></h1>

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

## Problema apresentado
### Busca
Implementar e comparar dois algoritmos de busca não informada (ex.: BFS, DFS, Custo Uniforme) e dois algoritmos de busca informada (Gulosa e A*) aplicados ao problema do labirinto.

Arquivo texto com grade retangular; caracteres permitidos: S (início), G (objetivo), # (parede), . (livre). Uma linha por linha do grid. Assim como é representado logo abaixo.

    S....
    .###.
    ..#..
    .###.
    ....G

## Arquivos

    
    Busca (não informada e informada)
        ├── informada
        |        ├── Busca Gulosa
        |        |   ├── data
        |        |   │   └── labirinto.txt
        |        │   └── src
        |        │       ├── BG.hpp
        |        │       └── main.cpp
        |        └── Ma
        └── não informada 
               ├── BFS
               |    ├── data
               |    │   └── labirinto.txt
               |    └── src
               |         ├── BFS.hpp
               |         └── main.cpp
               └── Ma


**/../../data/labiritmo.txt:** Arquivo que fica o layout do mapa do labirinto.

**/../../src/main.cpp:** Responsavel pela leitura do mapa e pela socicitação da chamada das funçãões da busca. E tambem é responsavel que mostrar se a operação ocorreu bem.

**/informada/Busca Gulosa/src/BG.hpp:** Onde é criado das todas as funções e structs da busca gulosa que serão executada executadas no decorrer do algoritmo.

**/não informada/BFS/src/BFS.hpp:** Onde é criado das todas as funções e structs da busca em largura que serão executada executadas no decorrer do algoritmo.

## Resolução do Problema



### Busca no Labirinto





## Conclusão 

