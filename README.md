# Trabalho 1 - Busca no Labirinto (Não Informada e Informada)

## Descrição

Implementação e comparação de algoritmos de busca aplicados ao problema do **labirinto** em ambiente de grade:

- **Busca Não Informada:**
  - BFS (Busca em Largura)
  - DFS (Busca em Profundidade)

- **Busca Informada:**
  - Busca Gulosa
  - A* (A-Estrela)

Ambos os algoritmos informados foram implementados com **duas heurísticas**:
- **Distância de Manhattan**
- **Distância Euclidiana**


## Estrutura do Projeto

```
INTELIGENCIA_ARTIFICIAL_BUSCA_E_8_RAINHAS/
├── .vscode/                               # Configurações do VSCode
│
├── Busca (não informada e informada)/     # Diretório principal dos algoritmos
│   ├── informada/
│   │   ├── A_Estrela/
│   │   │   ├── data/
│   │   │   │   └── labirinto.txt          # Mapa do labirinto usado no A*
│   │   │   └── src/
│   │   │       ├── A_Star.hpp             # Implementação do algoritmo A*
│   │   │       └── main.cpp               # Programa principal A*
│   │   │
│   │   └── Busca Gulosa/
│   │       ├── data/
│   │       │   └── labirinto.txt          # Mapa usado pela busca gulosa
│   │       └── src/
│   │           ├── BG.hpp                 # Implementação da Busca Gulosa
│   │           └── main.cpp               # Programa principal da Gulosa
│   │
│   ├── não informada/
│   │    ├── BFS/
│   │    │   ├── data/
│   │    │   │   └── labirinto.txt          # Dados para BFS
│   │    │   └── src/
│   │    │       ├── BFS.hpp                # Implementação da Busca em Largura
│   │    │       └── main.cpp               # Programa principal BFS
│   │    │
│   │    └── DFS/
│   │        ├── data/
│   │        │   └── labirinto.txt          # Dados para DFS
│   │        └── src/
│   │            ├── DFS.hpp                # Implementação da Busca em Profundidade
│   │            └── main.cpp               # Programa principal DFS
│   │
│   ├── out/
│   │   └── comparador                         # Binário gerado pelo comparador
│   │
│   ├── src_comparador/
│   │   ├── comparador_algoritmos.hpp          # Header com funções comparativas
│   │   └── labirinto.txt                      # Labirinto usado nos testes comparativos
│   └── main_comparar.cpp                  # Programa principal do comparador
│
├── README.md                              # Este arquivo (documentação principal)
├── SOLUCAO_CODIFICACAO.md                 # Relatório complementar (documentação extra)
└── .gitignore                             # Arquivos e pastas ignoradas pelo Git

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
cd "Busca (não informada e informada)"
g++ -o out/comparador main_comparar.cpp
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
- **Heurística**: Distância de Manhattan e Euclidiana
- **Estrutura**: Fila de prioridade (ordenada por h(n))

### 4. A* (A-Estrela)
- **Completude**: Sim (com heurística admissível)
- **Otimalidade**: Sim (com heurística admissível e consistente)
- **Heurística**: Distância de Manhattan e Euclidiana
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

Para os algoritmos de busca informada (Busca Gulosa e A*), foram utilizadas duas funções heurísticas: a Distância de Manhattan e a Distância Euclidiana.
Ambas estimam o custo restante até o objetivo a partir da posição atual.

### Distância de Manhattan
Utilizada por padrão nos algoritmos informados (Gulosa e A*), a Distância de Manhattan mede o custo em grids considerando apenas movimentos horizontais e verticais.

```cpp
h(n) = |x_atual - x_objetivo| + |y_atual - y_objetivo|
```

Propriedades:
- Admissível: nunca superestima o custo real até o objetivo.
- Consistente: h(n) ≤ c(n,n') + h(n') para todo sucessor n' de n.
- Ideal para: ambientes de grade com movimentos ortogonais (Norte, Sul, Leste, Oeste).

### Distância Euclidiana
A Distância Euclidiana considera o deslocamento direto entre o nó atual e o objetivo, representando o caminho “em linha reta”.
É mais precisa em ambientes contínuos ou quando são permitidos movimentos diagonais.

```cpp
h(n) = sqrt((x_atual - x_objetivo)^2 + (y_atual - y_objetivo)^2)
```

Propriedades:
- Produz estimativas mais realistas da distância ao objetivo.
- Pode não ser perfeitamente consistente em grids sem diagonais.
- Costuma reduzir o número de nós expandidos em relação à Manhattan.

## Exemplo de Saída


```
Executando comparação de algoritmos de busca...

Executando BFS...
Executando DFS...
Executando Busca Gulosa (Manhattan)...
Executando Busca Gulosa (Euclidiana)...
Executando A* (Manhattan)...
Executando A* (Euclidiana)...

==========================================================================================
                 COMPARATIVO DE ALGORITMOS DE BUSCA
==========================================================================================
Algoritmo         Tempo (s)   Memória  Nós Ger.   Nós Exp.   Custo   Solução Ótimo  
------------------------------------------------------------------------------------------
BFS               0.000084    17        18          15          8       SIM       SIM     
DFS               0.000033    10        11          8           8       SIM       NÃO    
Gulosa-Manh       0.000024    11        11          9           8       SIM       NÃO    
Gulosa-Eucl       0.000058    11        11          10          8       SIM       NÃO    
A*-Manh           0.000037    11        11          9           8       SIM       SIM     
A*-Eucl           0.000044    14        14          13          8       SIM       SIM     
==========================================================================================

ANÁLISE COMPARATIVA:

• Mais rápido: Gulosa-Manh (0.000024 s)
• Menor uso de memória: DFS (10 nós)
• Custo ótimo (menor caminho): 8 — obtido por BFS DFS Gulosa-Manh Gulosa-Eucl A*-Manh A*-Eucl 

==========================================================================================
```

# Análise dos Resultados

## Comparação Não Informados (BFS vs DFS)

### BFS
- Garantiu otimalidade (custo 8), mas usou mais memória (17 nós).  
- Expandiu mais nós (15) para garantir a solução ótima e apresentou maior tempo de execução em relação à DFS.

### DFS
- Usou menos memória (10 nós) e encontrou uma solução ótima por sorte neste caso.  
- Foi mais eficiente em tempo e nós expandidos (8), mas sem garantia de otimalidade em cenários gerais.

## Comparação Informados (Gulosa vs A*)

### A*
- Garantiu otimalidade (custo 8) com eficiência próxima à Busca Gulosa.  
- Utilizando as heurísticas Manhattan e Euclidiana, o A\* apresentou equilíbrio entre tempo, memória e qualidade da solução.  
- A versão com Manhattan foi ligeiramente mais rápida, enquanto a com Euclidiana teve estimativas mais precisas, porém com custo computacional um pouco maior.

### Gulosa
- Apresentou o menor tempo de execução, especialmente com a heurística Manhattan, priorizando os nós mais próximos ao objetivo.  
- Entretanto, não garante otimalidade, já que desconsidera o custo acumulado.  
- A variação Euclidiana também encontrou o mesmo custo (8), mas com leve aumento em tempo e número de nós expandidos.

## Ambos
- As buscas informadas mostraram-se muito mais eficientes que as não informadas, reduzindo significativamente o número de nós expandidos e o uso de memória.  
- O A\* é preferível quando a solução ótima é essencial, enquanto a Gulosa é vantajosa quando o tempo de resposta é prioridade.



## Impacto das Heurísticas (Manhattan e Euclidiana)

### Distância Manhattan
- Admissível e consistente em grades com movimentos ortogonais.  
- Apresentou excelente desempenho, guiando o A\*** de forma eficiente até o objetivo.

### Distância Euclidiana
- Também admissível, fornecendo uma estimativa mais realista da distância real em cenários com caminhos mais abertos.  
- Exigiu mais cálculos devido à raiz quadrada, resultando em leve aumento no tempo e memória, mas manteve a otimalidade no A\*.



## Eficiência Geral

- Os algoritmos informados (Gulosa e A\*), com ambas as heurísticas, expandiram menos nós (8–10) do que as buscas não informadas (BFS e DFS, 15–18).  
- Ambas as heurísticas respeitaram as propriedades de admissibilidade e consistência, garantindo correção teórica e bom desempenho.







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

## Contato

<table align="center">
  <tr>
    <th>Participantes</th>
    <th>Contato</th>
  </tr>
  <tr>
    <td>Maíra Beatriz de Almeida Lacerda</td>
    <td><a href="https://github.com/mairaallacerda"><img align="center" height="20px" width="90px" src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"/> </td>
  </tr>
  <tr>
      <td>Anderson Rodrigues dos Santos</td>
      <td><a href="https://github.com/anderrsantos"><img align="center" height="20px" width="90px" src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"/> </td>

  </tr>
</table>
