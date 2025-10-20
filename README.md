# Trabalho 1 - Busca no Labirinto (Não Informada e Informada)

## Descrição
Implementação e comparação de algoritmos de busca aplicados ao problema do labirinto:
- **Busca Não Informada**: BFS (Busca em Largura) e DFS (Busca em Profundidade)
- **Busca Informada**: Busca Gulosa e A* (A-Estrela)

## Estrutura do Projeto

```
Inteligencia_Artificial_Busca_e_8_Rainhas-main/
├── labirinto.txt                          # Arquivo de entrada do labirinto
├── comparador_algoritmos.cpp              # Sistema unificado de comparação
├── README.md                             # Este arquivo
├── Busca (não informada e informada)/
│   ├── não informada/
│   │   ├── BFS/
│   │   │   ├── src/
│   │   │   │   ├── BFS.hpp               # Implementação BFS
│   │   │   │   └── main.cpp              # Programa principal BFS
│   │   │   └── data/
│   │   │       └── labirinto.txt         # Dados para BFS
│   │   └── DFS/
│   │       ├── src/
│   │       │   ├── DFS.hpp               # Implementação DFS
│   │       │   └── main.cpp              # Programa principal DFS
│   │       └── data/
│   │           └── labirinto.txt         # Dados para DFS
│   └── informada/
│       ├── Busca Gulosa/
│       │   ├── src/
│       │   │   ├── BG.hpp                # Implementação Busca Gulosa
│       │   │   └── main.cpp              # Programa principal Gulosa
│       │   └── data/
│       │       └── labirinto.txt         # Dados para Gulosa
│       └── A_Estrela/
│           ├── src/
│           │   ├── A_Star.hpp            # Implementação A*
│           │   └── main.cpp              # Programa principal A*
│           └── data/
│               └── labirinto.txt         # Dados para A*
```

## Formato do Labirinto
O labirinto é representado em um arquivo de texto (`labirinto.txt`) com os seguintes caracteres:
- `S`: Posição inicial (Start)
- `G`: Posição objetivo (Goal)  
- `#`: Parede/obstáculo
- `.`: Espaço livre

**Exemplo:**
```
S....
.###.
..#..
.###.
....G
```

## Como Executar

### Requisitos
- Compilador C++ (g++)
- Sistema operacional: Windows, Linux ou macOS

### Compilação e Execução

#### 1. Algoritmos Individuais

**BFS (Busca em Largura):**
```bash
cd "Busca (não informada e informada)/não informada/BFS/src"
g++ -o bfs main.cpp
./bfs
```

**DFS (Busca em Profundidade):**
```bash
cd "Busca (não informada e informada)/não informada/DFS/src"
g++ -o dfs main.cpp
./dfs
```

**Busca Gulosa:**
```bash
cd "Busca (não informada e informada)/informada/Busca Gulosa/src"
g++ -o gulosa main.cpp
./gulosa
```

**A* (A-Estrela):**
```bash
cd "Busca (não informada e informada)/informada/A_Estrela/src"
g++ -o astar main.cpp
./astar
```

#### 2. Comparação Unificada (Recomendado)

Para executar todos os algoritmos e gerar uma análise comparativa:

```bash
# No diretório raiz do projeto
g++ -o out/comparador comparador_algoritmos.cpp
./out/comparador
```

## Algoritmos Implementados

### 1. BFS (Busca em Largura)
- **Completude**: Sim (sempre encontra solução se existir)
- **Otimalidade**: Sim (encontra caminho com menor número de passos)
- **Complexidade Temporal**: O(b^d)
- **Complexidade Espacial**: O(b^d)
- **Estrutura**: Fila (FIFO)

### 2. DFS (Busca em Profundidade)
- **Completude**: Não (pode entrar em loop infinito)
- **Otimalidade**: Não (pode encontrar solução não-ótima)
- **Complexidade Temporal**: O(b^m)
- **Complexidade Espacial**: O(bm)
- **Estrutura**: Pilha (LIFO)

### 3. Busca Gulosa
- **Completude**: Não (pode ficar presa em mínimos locais)
- **Otimalidade**: Não (escolhe sempre a opção que parece melhor localmente)
- **Heurística**: Distância de Manhattan
- **Estrutura**: Fila de prioridade (ordenada por h(n))

### 4. A* (A-Estrela)
- **Completude**: Sim (com heurística admissível)
- **Otimalidade**: Sim (com heurística admissível e consistente)
- **Heurística**: Distância de Manhattan (admissível para este problema)
- **Função de Avaliação**: f(n) = g(n) + h(n)
- **Estrutura**: Fila de prioridade (ordenada por f(n))

## Métricas Coletadas

Para cada algoritmo, são medidas as seguintes métricas:

1. **Tempo de Execução**: Tempo em segundos para encontrar a solução
2. **Memória Máxima**: Número máximo de nós mantidos simultaneamente (fronteira + explorados)
3. **Nós Gerados**: Total de nós criados durante a busca
4. **Nós Expandidos**: Total de nós cujos sucessores foram examinados
5. **Custo do Caminho**: Número de passos na solução encontrada
6. **Completude**: Se o algoritmo encontrou uma solução
7. **Otimalidade**: Se a solução encontrada é ótima

## Heurística Utilizada

Para os algoritmos informados (Gulosa e A*), utilizamos a **Distância de Manhattan**:

```cpp
h(n) = |x_atual - x_objetivo| + |y_atual - y_objetivo|
```

Esta heurística é:
- **Admissível**: Nunca superestima o custo real até o objetivo
- **Consistente**: h(n) ≤ c(n,n') + h(n') para todo sucessor n' de n

## Exemplo de Saída

```
Executando comparação de algoritmos de busca no labirinto...

Executando BFS...
Executando DFS...
Executando Busca Gulosa...
Executando A*...

================================================================================
                    RESULTADOS COMPARATIVOS
================================================================================
Algoritmo      Tempo (s)   Memória   Nós Ger.    Nós Exp.    Custo   Solução   Ótimo
--------------------------------------------------------------------------------
BFS            0.000000    17        18          15          8       SIM       SIM
DFS            0.000000    10        11          8           8       SIM       NÃO
Gulosa         0.000000    11        11          9           8       SIM       NÃO
A*             0.000000    11        11          9           8       SIM       SIM
================================================================================

ANÁLISE COMPARATIVA:

• Algoritmo mais rápido: BFS (0.000000s)
• Algoritmo com menor uso de memória: DFS (10 nós)
• Algoritmo(s) ótimo(s): BFS A* (custo 8)
```

## Análise dos Resultados

### Comparação Não Informados (BFS vs DFS)
- **BFS**: Garantiu otimalidade (custo 8) mas usou mais memória (17 nós)
- **DFS**: Usou menos memória (10 nós) e encontrou solução ótima por sorte neste caso
- **BFS**: Expandiu mais nós (15) para garantir otimalidade
- **DFS**: Mais eficiente em nós expandidos (8) mas sem garantia de otimalidade

### Comparação Informados (Gulosa vs A*)
- **A***: Garantiu otimalidade (custo 8) com mesma eficiência da Gulosa (9 nós expandidos)
- **Gulosa**: Mesma performance que A* neste labirinto específico, mas sem garantia
- **Ambos**: Usaram heurística Manhattan eficientemente (11 nós de memória)
- **A***: Preferível por combinar eficiência com garantia de otimalidade

### Impacto da Heurística Manhattan
- **Algoritmos informados**: Expandiram significativamente menos nós (9 vs 8-15)
- **Admissibilidade**: A* garantiu otimalidade com h(n) ≤ h*(n)
- **Consistência**: h(n) ≤ c(n,n') + h(n') sempre respeitada
- **Eficiência**: Heurística guiou busca diretamente ao objetivo

## Dependências
- Compilador C++11 ou superior
- Bibliotecas padrão: `<iostream>`, `<vector>`, `<queue>`, `<stack>`, `<set>`, `<map>`, `<chrono>`, `<algorithm>`

## Observações Técnicas

### Problemas de Codificação
Se a saída apresentar caracteres estranhos (como `├º`, `├│`, `ÔÇó`), isso é devido à codificação UTF-8 vs Windows-1252. Os resultados numéricos permanecem corretos. Para resolver:

**Windows Command Prompt:**
```cmd
chcp 65001
```

**Linux/macOS:**
```bash
export LANG=en_US.UTF-8
```

### Interpretação dos Resultados Específicos
- **Tempo 0.000000s**: Normal para labirinto pequeno - execução muito rápida (microssegundos)
- **Custo ótimo 8**: Caminho mínimo de S(0,0) até G(4,4) considerando obstáculos
- **Todos encontraram custo 8**: Labirinto permite múltiplos caminhos ótimos
- **DFS encontrou ótimo**: Sorte devido à ordem de exploração e simplicidade do labirinto
- **Memória**: BFS (17) > Gulosa/A* (11) > DFS (10) - conforme esperado teoricamente
- **Nós expandidos**: DFS (8) < Gulosa/A* (9) < BFS (15) - heurística mostrou eficiência

