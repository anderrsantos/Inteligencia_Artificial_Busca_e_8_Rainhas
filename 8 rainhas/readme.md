# Trabalho 2 - 8 Rainhas com Hill Climbing

## Descrição

Implementação do problema das **8 Rainhas** utilizando o algoritmo de **Hill Climbing**, com duas variações:

- **Hill Climbing com Movimentos Laterais**
- **Hill Climbing com Reinício Aleatório (Random Restart)**

O objetivo é posicionar as 8 rainhas em um tabuleiro \(8 \times 8\) de maneira que nenhuma ataque a outra. Foram analisados e comparados o tempo de execução, a taxa de sucesso e o número de reinícios nas duas variações implementadas.

## Estrutura do Projeto
```
INTELIGENCIA_ARTIFICIAL_BUSCA_E_8_RAINHAS/
├── .vscode/                                # Configurações do VSCode
│
├── 8 rainhas/                              # Diretório principal do algoritmo
│   ├── src/
│   │   ├── mov.hpp                         # Implementação dos algoritmos (Hill Climbing)
│   │   ├── tabuleiro.hpp                   # Implementação do tabuleiro e conflito
│   │   └── main.cpp                        # Arquivo principal com a execução do algoritmo
│   └── README.md                           # Este arquivo (documentação principal)

```


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

Após clonar ou baixar o repositório, compile o código com o seguinte comando:
   
```bash
cd "8 rainhas/src"
g++ -o main main.cpp
./main
```

## Algoritmos Implementados

### 1. Hill Climbing com Movimentos Laterais
- **Completude**: Não garante que sempre encontrará uma solução.
- **Otimalidade**: Não garante solução ótima, pois pode ficar preso em máximos locais.
- **Complexidade Temporal**: Depende do número de interações (50).
- **Complexidade Espacial**: O(n), onde n é o número de rainhas.


### 2. Hill Climbing com Reinício Aleatório
- **Completude**: Sim, garante que sempre encontrará uma solução se houver tempo e reinícios suficiente
- **Otimalidade**: Não garante solução ótima, mas aumenta a probabilidade de encontrar uma solução global.
- **Complexidade Temporal**:Depende do número de reinícios e interações.
- **Complexidade Espacial**: O(n), onde n é o número de rainhas.


## Exemplo de Saída

O programa resolverá o problema das 8 rainhas utilizando as variações de Hill Climbing e exibirá o estado final do tabuleiro, o número de movimentos realizados, o tempo de execução e outros parâmetros.

```
 =================================================================
 Resolvendo com Hill Climbing com movimentos laterais com máximo de 50 interações.

 Tabuleiro resolvido: 0 4 7 5 2 6 1 3 
 Número de conflitos atual: 0
 Número de iterações: 50
 Tempo de execução: 0.003 segundos
 =================================================================
 Resolvendo com Hill Climbing com REINÍCIOS ALEATÓRIOS (Random-Restart), com máximo de 50 interações e 50 reinícios.

 Tabuleiro resolvido: 0 4 7 5 2 6 1 3
 Número de conflitos atual: 0
 Número de iterações totais: 150
 Número de reinícios: 3
 Tempo de execução: 0.005 segundos
 =================================================================
```

## Análise de Resultados

### Hill Climbing com Movimentos Laterais

O algoritmo de **Hill Climbing com Movimentos Laterais** foi eficiente ao escapar de platôs rasos, aumentando a taxa de sucesso para **87%**. No entanto, a execução exigiu mais movimentos em comparação à versão com reinício aleatório. Isso acontece porque o algoritmo realiza movimentos que não alteram \( h(n) \) (\(\Delta h = 0\)) até atingir o limite de iterações, o que ajuda a evitar estagnação, mas também aumenta o custo de cada execução.

#### Métricas:
- **Tempo de Execução:** 1.02 ms
- **Taxa de Sucesso:** 87%
- **Movimentos Médios:** 55
- **Número de Reinícios:** 0

### Hill Climbing com Reinício Aleatório

O algoritmo **Hill Climbing com Reinício Aleatório** obteve **100% de sucesso** em todas as execuções. Essa variação foi eficaz para escapar de máximos locais, pois reinicia o algoritmo sempre que uma solução local é encontrada. Embora o tempo de execução tenha sido ligeiramente maior devido ao número de reinícios, o número de iterações por reinício foi controlado, garantindo que o algoritmo sempre encontrasse uma solução.

#### Métricas:
- **Tempo de Execução:** 1.15 ms
- **Taxa de Sucesso:** 100%
- **Movimentos Médios:** 61
- **Número de Reinícios:** 2.3 (média por execução)

### Comparação entre os Algoritmos

| **Algoritmo**                        | **Tempo (ms)** | **Reinícios** | **Taxa de Sucesso** | **Movimentos Médios** |
|--------------------------------------|----------------|---------------|---------------------|-----------------------|
| Hill Climbing (Movimentos Laterais)  | 1.02           | 0             | 87%                 | 55                    |
| Hill Climbing (Reinício Aleatório)   | 1.15           | 2.3           | 100%                | 61                    |

#### Observações:
- **Hill Climbing com Movimentos Laterais** teve um desempenho muito bom, mas o número de movimentos aumentou porque o algoritmo não realizava mudanças de estado que não resultassem em uma melhoria no número de conflitos (\( h(n) = 0 \)).
- **Hill Climbing com Reinício Aleatório** teve **100% de sucesso**, o que o torna a solução mais confiável, mas com custo de execução maior devido aos múltiplos reinícios.

### Conclusões:

- O **Hill Climbing com Movimentos Laterais** é uma boa alternativa para situações onde é necessário escapar de platôs, mas o aumento do número de movimentos pode ser um trade-off em termos de tempo de execução.
- O **Hill Climbing com Reinício Aleatório** é mais confiável e garante a solução, mas pode ser mais lento dependendo do número de reinícios.
  
Em resumo, a versão com **reinício aleatório** foi a mais robusta, com uma taxa de sucesso de 100%, embora o tempo de execução tenha sido ligeiramente maior devido ao maior número de reinícios. A escolha do algoritmo depende dos requisitos específicos de eficiência versus confiabilidade.



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
