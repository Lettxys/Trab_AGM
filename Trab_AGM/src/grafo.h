#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

struct Aresta {
    int v;         // vértice de destino
    double peso;   // peso da aresta (usamos double por causa das distâncias geométricas)
};

// Grafo é um vetor onde cada posição representa um vértice, 
// e dentro dessa posição guardamos a lista de arestas que saem dele.
using Grafo = std::vector<std::vector<Aresta>>;


Grafo criarGrafo(int V);

void adicionarAresta(Grafo& g, int u, int v, double peso);

Grafo gerarGrafoEsparso(int V);

Grafo gerarGrafoDenso(int V);

Grafo gerarGrafoGeometrico(int V);

#endif