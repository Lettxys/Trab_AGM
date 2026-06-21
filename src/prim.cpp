#include "prim.h"
#include <iostream>
#include <vector>
#include <set>
#include <limits>

double executarPrim(const Grafo& g, int verticeInicial, bool imprimir) {
    int V = g.size();

    // u.chave = ∞  e  u.π = NIL (-1)
    std::vector<double> chave(V, std::numeric_limits<double>::infinity());
    std::vector<int> pai(V, -1);
    std::vector<bool> naFila(V, true);

    chave[verticeInicial] = 0.0;

    std::set<std::pair<double, int>> Q;
    for (int i = 0; i < V; i++) {
        Q.insert({chave[i], i});
    }

    double pesoTotalAGM = 0.0;

    while (!Q.empty()) {
        auto it = Q.begin();
        int u = it->second;
        Q.erase(it); 
        naFila[u] = false; 

        if (pai[u] != -1) {
            pesoTotalAGM += chave[u];
        }

        for (const auto& aresta : g[u]) {
            int v = aresta.v;
            double peso_uv = aresta.peso;

            if (naFila[v] && peso_uv < chave[v]) {
                
                Q.erase({chave[v], v});
                
                pai[v] = u;
                chave[v] = peso_uv;
 
                Q.insert({chave[v], v});
            }
        }
    }

    if (imprimir) {
        std::cout << "=== RESULTADO DO ALGORITMO DE PRIM ===\n";
        std::cout << "Peso Total da AGM: " << pesoTotalAGM << "\n";
        std::cout << "Arestas pertencentes a AGM (Pai -> Filho):\n";
        for (int i = 0; i < V; i++) {
            if (pai[i] != -1) {
                std::cout << "  " << pai[i] << " - " << i << " (Peso: " << chave[i] << ")\n";
            }
        }
    }

    return pesoTotalAGM;
}
