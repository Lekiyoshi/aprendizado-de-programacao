"""
By Lkiyoshi
Scanner simples de arquivos .txt
para o instanciamento de grafos
com matriz e lista de adjacências.
"""

# from pprint import pprint
from tabulate import tabulate


class Grafo:
    def __init__(self, nome_arquivo):
        self.tamanho = 0
        self.rotulos = []
        self.matriz_adj = []
        self.lista_adj = []
        self.__scan_txt(nome_arquivo)

    # O scanner não contém tratamento de excessões
    # O arquivo .txt precisa seguir um formato específico para evitar erros
    def __scan_txt(self, nome_arquivo):
        with open(nome_arquivo, 'rt') as f:
            linha = f.readline()
            self.tamanho = int(linha.split()[0])

            linha = f.readline()
            rotulos = linha.split()
            for i, r in enumerate(rotulos):
                if i > self.tamanho:
                    break
                self.rotulos.append(r)

            for i in range(0, self.tamanho):
                linha = f.readline()
                adj = linha.split()
                self.matriz_adj.append([])
                for j in range(0, self.tamanho):
                    self.matriz_adj[i].append(int(adj[j]))

        for i in range(0, self.tamanho):
            for j in range(0, self.tamanho):
                if self.matriz_adj[i][j] != 0:
                    self.lista_adj.append((self.rotulos[j], self.rotulos[i], self.matriz_adj[i][j]))


if __name__ == "__main__":
    grafo = Grafo("grafo.txt")

    print("Tamanho:", grafo.tamanho)
    print("Rótulos:", grafo.rotulos)
    print()
    print("Matriz de adjacências:")
    print(tabulate(grafo.matriz_adj, headers=grafo.rotulos, showindex=grafo.rotulos))
    print()
    print("Lista de adjacências:")
    print(tabulate(grafo.lista_adj, headers=["Origem", "Destino", "Peso"], showindex=True))
