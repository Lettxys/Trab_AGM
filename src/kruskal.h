#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "grafo.h"
#include <vector>

struct ArestaKruskal {
    int u;
    int v;
    double peso;
};

double executarKruskal(const Grafo& g, bool imprimir = true);

#endif
