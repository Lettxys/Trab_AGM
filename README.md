# Trabalho Prático - Árvore Geradora Mínima (AGM)

Implementação e análise experimental dos algoritmos de **Prim** e **Kruskal**
para o problema da Árvore Geradora Mínima.

Disciplina: Algoritmos em Grafos

**Integrantes:**
- Elislândia Aparecida Horlanda da Silva
- Leticia Almeida Lima
- Isabelli Araujo Pinho

## Estrutura do projeto

```text
TRAB_AGM/
+-- src/
|   +-- grafo.h / grafo.cpp
|   +-- prim.h / prim.cpp
|   +-- kruskal.h / kruskal.cpp
|   +-- main.cpp
+-- docs/
|   +-- Relatorio_AGM.pdf
|   +-- grafico_esparso.png
|   +-- grafico_denso.png
|   +-- grafico_geometrico.png
+-- gerar_graficos.py
+-- resultados_agm.csv
+-- programa_agm.exe
+-- README.md
```

Organização usada:

- `src/`: guarda apenas o código-fonte em C++.
- `docs/`: guarda relatório e arquivos usados no relatório, como os graficos gerados.
- `resultados_agm.csv`: arquivo gerado pelo programa com as métricas dos testes.
- `gerar_graficos.py`: script que lê o CSV e gera os gráficos.
- `programa_agm.exe`: executável gerado pela compilação no Windows. 

Observação: `programa_agm.exe`, `resultados_agm.csv` e os gráficos podem ser
gerados novamente. O mais importante para recompilar o trabalho é manter
`src/`, `README.md` e `gerar_graficos.py`.

## O que o programa faz

O programa gera grafos de teste e compara os algoritmos de Prim e Kruskal.
Para cada caso, ele executa cada algoritmo 10 vezes e calcula:

- tempo médio de execução;
- desvio padrão;
- peso total da AGM;
- tempo de construção do grafo.

Os resultados são mostrados no terminal e também salvos no arquivo:

```text
resultados_agm.csv
```

## Tipos de grafo testados

| Tipo | Descrição |
|---|---|
| Esparso | Corrente inicial para garantir conexidade, mais algumas arestas extras com pesos aleatórios |
| Denso | Aproximadamente 80% das arestas possíveis, com pesos aleatórios |
| Geometrico | Pontos no plano [0,1] x [0,1], com pesos calculados pela distância euclidiana |

## Passo a passo para executar no Windows

### 1. Abrir o terminal

Abra o **PowerShell**.

### 2. Entrar na pasta do projeto

Execute:

```powershell
cd "caminho-da-pasta"
```

Troque o caminho acima pelo caminho da sua pasta, conforme indicado.

### 3. Verificar se o g++ esta funcionando

Execute:

```powershell
g++ --version
```

### 4. Compilar o programa

Execute:

```powershell
g++ -O2 src/main.cpp src/grafo.cpp src/prim.cpp src/kruskal.cpp -o programa_agm.exe
```

Se não aparecer nenhuma mensagem de erro, a compilação deu certo.

### 5. Executar o programa

Execute:

```powershell
.\programa_agm.exe
```

O programa vai imprimir os resultados no terminal. Ao final, ele cria ou
atualiza o arquivo `resultados_agm.csv`.

## Como gerar os gráficos

Depois de executar o programa e gerar `resultados_agm.csv`, rode:

```powershell
python gerar_graficos.py
```

O script `gerar_graficos.py` procura estes arquivos/pastas:

```text
resultados_agm.csv
docs/
```

Ele lê os dados de `resultados_agm.csv` e salva os gráficos na pasta `docs/`:

```text
docs/grafico_esparso.png
docs/grafico_denso.png
docs/grafico_geometrico.png
```

Esses gráficos estão no relatório. O eixo horizontal representa o
tamanho da instância, ou seja, o número de vertices. O eixo vertical representa
o tempo médio de execução em milissegundos.

## Passo a passo no Linux

Dentro da pasta principal do projeto, compile com:

```bash
g++ -O2 src/main.cpp src/grafo.cpp src/prim.cpp src/kruskal.cpp -o programa_agm
```

Depois execute:

```bash
./programa_agm
```

Para gerar os gráficos:

```bash
python3 gerar_graficos.py
```

## Observação sobre os tamanhos

Os grafos esparsos usam tamanhos maiores. Os grafos densos e geométricos usam
tamanhos menores para evitar consumo muito alto de memória e tempo, pois esses
casos crescem mais rapidamente.

## Referências

- CORMEN, Thomas H.; LEISERSON, Charles E.; RIVEST, Ronald L.; STEIN, Clifford. **Introduction to Algorithms**. 3. ed. MIT Press, 2009.
- SEDGEWICK, Robert; WAYNE, Kevin. **Algorithms**. 4. ed. Addison-Wesley, 2011.
- KLEINBERG, Jon; TARDOS, Eva. **Algorithm Design**. Pearson, 2005.
