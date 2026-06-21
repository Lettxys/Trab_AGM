#include "grafo.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>

Grafo criarGrafo(int V) {
    return Grafo(V);
}

void adicionarAresta(Grafo& g, int u, int v, double peso) {
    g[u].push_back({v, peso});
    g[v].push_back({u, peso});
}


// |E| ≈ V + V/10
Grafo gerarGrafoEsparso(int V) {
    Grafo g = criarGrafo(V);
    for (int i = 0; i < V - 1; i++)
        adicionarAresta(g, i, i + 1, (rand() % 100) + 1.0);

    int extras = V / 10;
    for (int i = 0; i < extras; i++) {
        int u = rand() % V, v = rand() % V;
        if (u != v)
            adicionarAresta(g, u, v, (rand() % 100) + 1.0);
    }
    return g;
}


// |E| ≈ 0.8 × V(V-1)/2
Grafo gerarGrafoDenso(int V) {
    Grafo g = criarGrafo(V);

    // corrente base garante conexidade
    for (int i = 0; i < V - 1; i++)
        adicionarAresta(g, i, i + 1, (rand() % 100) + 1.0);

    // adiciona 80% das arestas restantes
    for (int u = 0; u < V; u++)
        for (int v = u + 2; v < V; v++)   // u+2 para não duplicar a corrente
            if (rand() % 10 < 8)          
                adicionarAresta(g, u, v, (rand() % 100) + 1.0);

    return g;
}

Grafo gerarGrafoGeometrico(int V) {
    Grafo g = criarGrafo(V);

    // gera coordenadas aleatórias
    std::vector<double> x(V), y(V);
    for (int i = 0; i < V; i++) {
        x[i] = (rand() % 10000) / 10000.0;
        y[i] = (rand() % 10000) / 10000.0;
    }

    auto dist = [&](int a, int b) {
        double dx = x[a] - x[b], dy = y[a] - y[b];
        return std::sqrt(dx*dx + dy*dy);
    };

    // corrente base garante que o grafo sera conexo
    for (int i = 0; i < V - 1; i++)
        adicionarAresta(g, i, i + 1, dist(i, i + 1));

    int K = 4;
    for (int u = 0; u < V; u++) {
        std::vector<std::pair<double, int>> vizinhos;
        for (int v = 0; v < V; v++)
            if (v != u) vizinhos.push_back({dist(u, v), v});
        std::sort(vizinhos.begin(), vizinhos.end());

        for (int i = 0; i < K && i < (int)vizinhos.size(); i++) {
            int v = vizinhos[i].second;
            bool jaExiste = false;
            for (auto& a : g[u])
                if (a.v == v) { jaExiste = true; break; }
            if (!jaExiste)
                adicionarAresta(g, u, v, vizinhos[i].first);
        }
    }
    return g;
}
