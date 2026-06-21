#include "kruskal.h"
#include <iostream>
#include <vector>
#include <algorithm>

int encontrar(int i, std::vector<int>& pai) {
    if (pai[i] == -1) return i;
    return pai[i] = encontrar(pai[i], pai);
}

void unir(int x, int y, std::vector<int>& pai, std::vector<int>& rank) {
    int raizX = encontrar(x, pai);
    int raizY = encontrar(y, pai);
    if (raizX == raizY) return;

    // union by rank: árvore menor pendurada na maior
    if (rank[raizX] < rank[raizY]) std::swap(raizX, raizY);
    pai[raizY] = raizX;
    if (rank[raizX] == rank[raizY]) rank[raizX]++;
}

double executarKruskal(const Grafo& g, bool imprimir) {
    int V = g.size();
    std::vector<ArestaKruskal> todasArestas;

    for (int u = 0; u < V; u++)
        for (const auto& viz : g[u])
            if (u < viz.v)
                todasArestas.push_back({u, viz.v, viz.peso});

    std::sort(todasArestas.begin(), todasArestas.end(),
              [](const ArestaKruskal& a, const ArestaKruskal& b) {
                  return a.peso < b.peso;
              });

    std::vector<int> pai(V, -1);
    std::vector<int> rank(V, 0); // necessario para union by rank

    std::vector<ArestaKruskal> agm;
    double pesoTotal = 0.0;

    for (const auto& aresta : todasArestas) {
        int cu = encontrar(aresta.u, pai);
        int cv = encontrar(aresta.v, pai);

        if (cu != cv) {
            agm.push_back(aresta);
            pesoTotal += aresta.peso;
            unir(cu, cv, pai, rank);
        }

        if ((int)agm.size() == V - 1) break;
    }

    if (imprimir) {
        std::cout << "=== RESULTADO DO ALGORITMO DE KRUSKAL ===\n";
        std::cout << "Peso Total da AGM: " << pesoTotal << "\n";
        std::cout << "Arestas pertencentes a AGM:\n";
        for (const auto& a : agm)
            std::cout << "  " << a.u << " - " << a.v << " (Peso: " << a.peso << ")\n";
    }

    return pesoTotal;
}
