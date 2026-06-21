#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>
#include "grafo.h"
#include "prim.h"
#include "kruskal.h"

double calcularMedia(const std::vector<double>& valores) {
    double soma = 0.0;
    for (double v : valores) soma += v;
    return soma / valores.size();
}

double calcularDesvio(const std::vector<double>& valores, double media) {
    double somaQuadrados = 0.0;
    for (double v : valores)
        somaQuadrados += (v - media) * (v - media);
    return std::sqrt(somaQuadrados / valores.size());
}

void executarExperimento(const std::string& nome,
                         const std::vector<int>& tamanhos,
                         Grafo (*gerador)(int),
                         int execucoes,
                         std::ofstream& csv) {
    std::cout << "\n==================================================\n";
    std::cout << "TIPO DE GRAFO: " << nome << "\n";
    std::cout << "==================================================\n";

    for (int V : tamanhos) {
        std::cout << "\n--------------------------------------------------\n";
        std::cout << "Testando com V = " << V << "\n";
        std::cout << "--------------------------------------------------\n";

        auto inicioConstrucao = std::chrono::high_resolution_clock::now();
        Grafo g = gerador(V);
        auto fimConstrucao = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duracaoConstrucao =
            fimConstrucao - inicioConstrucao;

        std::cout << "Tempo de construcao do grafo: "
                  << duracaoConstrucao.count() << " ms\n";

        if (V == tamanhos.front()) {
            std::cout << "\nExemplo de AGM para a menor instancia:\n";
            executarPrim(g, 0, true);
            executarKruskal(g, true);
        }

        std::vector<double> temposPrim;
        std::vector<double> temposKruskal;
        double pesoPrim = 0.0;
        double pesoKruskal = 0.0;

        for (int i = 0; i < execucoes; i++) {
            auto inicio = std::chrono::high_resolution_clock::now();
            double peso = executarPrim(g, 0, false);
            auto fim = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duracao = fim - inicio;
            temposPrim.push_back(duracao.count());
            if (i == 0) pesoPrim = peso;
        }

        for (int i = 0; i < execucoes; i++) {
            auto inicio = std::chrono::high_resolution_clock::now();
            double peso = executarKruskal(g, false);
            auto fim = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duracao = fim - inicio;
            temposKruskal.push_back(duracao.count());
            if (i == 0) pesoKruskal = peso;
        }

        double mediaPrim = calcularMedia(temposPrim);
        double desvioPrim = calcularDesvio(temposPrim, mediaPrim);
        double mediaKruskal = calcularMedia(temposKruskal);
        double desvioKruskal = calcularDesvio(temposKruskal, mediaKruskal);

        std::cout << "\nMETRICAS (media de " << execucoes << " execucoes):\n";
        std::cout << "Prim    - Media: " << mediaPrim
                  << " ms | Desvio: " << desvioPrim
                  << " ms | Peso: " << pesoPrim << "\n";
        std::cout << "Kruskal - Media: " << mediaKruskal
                  << " ms | Desvio: " << desvioKruskal
                  << " ms | Peso: " << pesoKruskal << "\n";

        if (std::abs(pesoPrim - pesoKruskal) > 0.000001) {
            std::cout << "Aviso: os pesos de Prim e Kruskal ficaram diferentes.\n";
        }

        csv << nome << ","
            << V << ","
            << duracaoConstrucao.count() << ","
            << mediaPrim << ","
            << desvioPrim << ","
            << mediaKruskal << ","
            << desvioKruskal << ","
            << pesoPrim << ","
            << pesoKruskal << "\n";
    }
}

int main() {
    srand(42); // semente fixa para repetir os mesmos grafos

    int execucoes = 10;

    std::vector<int> tamanhosEsparso = {100, 500, 1000, 5000, 10000};
    std::vector<int> tamanhosDenso = {100, 200, 400, 600, 800};
    std::vector<int> tamanhosGeometrico = {100, 300, 500, 800, 1000};

    std::ofstream csv("resultados_agm.csv");
    if (!csv) {
        std::cerr << "Erro ao criar o arquivo resultados_agm.csv\n";
        return 1;
    }

    csv << "tipo,V,tempo_construcao_ms,media_prim_ms,desvio_prim_ms,"
        << "media_kruskal_ms,desvio_kruskal_ms,peso_prim,peso_kruskal\n";

    std::cout << "==================================================\n";
    std::cout << "AGM: Prim e Kruskal\n";
    std::cout << "==================================================\n";

    executarExperimento("Esparso", tamanhosEsparso, gerarGrafoEsparso, execucoes, csv);
    executarExperimento("Denso", tamanhosDenso, gerarGrafoDenso, execucoes, csv);
    executarExperimento("Geometrico", tamanhosGeometrico, gerarGrafoGeometrico, execucoes, csv);

    std::cout << "\nResultados salvos em resultados_agm.csv\n";

    return 0;
}
