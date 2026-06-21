# Script para plotar os gráficos do relatório
# Ele lê resultados_agm.csv e salva as imagens na pasta docs

import csv
from pathlib import Path

import matplotlib.pyplot as plt


PASTA_PROJETO = Path(__file__).resolve().parent
ARQUIVO_CSV = PASTA_PROJETO / "resultados_agm.csv"
PASTA_GRAFICOS = PASTA_PROJETO / "docs"


if not ARQUIVO_CSV.exists():
    print("Arquivo resultados_agm.csv nao encontrado.")
    print("Execute primeiro o programa AGM para gerar esse arquivo.")
    raise SystemExit(1)

dados = {}

with open(ARQUIVO_CSV, newline="", encoding="utf-8") as arquivo:
    leitor = csv.DictReader(arquivo)

    for linha in leitor:
        tipo = linha["tipo"]

        if tipo not in dados:
            dados[tipo] = {
                "V": [],
                "Prim": [],
                "Kruskal": []
            }

        dados[tipo]["V"].append(int(linha["V"]))
        dados[tipo]["Prim"].append(float(linha["media_prim_ms"]))
        dados[tipo]["Kruskal"].append(float(linha["media_kruskal_ms"]))

for tipo, valores in dados.items():
    plt.figure(figsize=(8, 5))

    plt.plot(valores["V"], valores["Prim"], marker="o", label="Prim")
    plt.plot(valores["V"], valores["Kruskal"], marker="o", label="Kruskal")

    plt.title(f"Tempo de execução - Grafo {tipo}")
    plt.xlabel("Tamanho da instância (número de vértices)")
    plt.ylabel("Tempo médio de execução (ms)")

    plt.grid(True)
    plt.legend()
    plt.tight_layout()

    nome_arquivo = PASTA_GRAFICOS / f"grafico_{tipo.lower()}.png"
    plt.savefig(nome_arquivo, dpi=300)
    plt.close()

    print(f"Grafico salvo: {nome_arquivo}")
