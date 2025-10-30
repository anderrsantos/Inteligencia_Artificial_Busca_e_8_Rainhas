# Trabalho 2 - 8 Rainhas com Hill Climbing

## Descrição

Implementação do problema das **8 Rainhas** utilizando o algoritmo de **Hill Climbing**, com duas variações:

- **Hill Climbing com Movimentos Laterais**
- **Hill Climbing com Reinício Aleatório (Random Restart)**

O objetivo é posicionar as 8 rainhas em um tabuleiro \(8 \times 8\) de maneira que nenhuma ataque a outra. Foram analisados e comparados o tempo de execução, a taxa de sucesso e o número de reinícios nas duas variações implementadas.

## Estrutura do Projeto



## Algoritmos Implementados

### 1. Hill Climbing com Movimentos Laterais

- **Objetivo:** Resolver o problema permitindo que o algoritmo realize movimentos laterais (sem alteração de \( h \)) para escapar de platôs rasos.
- **Limite:** 50 interações máximas.

### 2. Hill Climbing com Reinício Aleatório

- **Objetivo:** Resolver o problema reiniciando o algoritmo sempre que atinge um máximo local.
- **Limite:** 50 reinícios máximos e 50 interações por reinício.

## Como Executar

### Requisitos

- Compilador C++ (g++ ou equivalente)
- Sistema operacional: Windows, Linux ou macOS

### Compilação e Execução

1. **Compilar o código:**

   Após clonar ou baixar o repositório, compile o código com o seguinte comando:
   
```bash
cd "8 rainhas/src"
g++ -o main main.cpp
./main
```

