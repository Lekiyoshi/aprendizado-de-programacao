// Trabalho II de Estrutura de Dados I
// Gerador de árvore binária com n elementos aleatórios e métodos de travessia
// Escrito por LeviK

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include "binary_tree.h"

using namespace std;

int main() {
	srand(time(NULL));

	Node* raiz = NULL;
	int opcao, n;

	do {
		cout << "+ - - - - - - - - - - MENU - - - - - - - - - - +\n";
		cout << "| 1. Gerar arvore binaria completa             |\n";
		cout << "| 2. Gerar arvore binaria randomizada          |\n";
		cout << "| 3. Sair                                      |\n";
		cout << "+ - - - - - - - - - - -  - - - - - - - - - - - +\n";

		cout << "\n";
		cout << "Escolha uma opcao: ";
		cin >> opcao;
		cout << "\n";

		switch (opcao) {
		case 1:
			cout << "Digite a quantidade de elementos da arvore binaria completa: ";
			cin >> n;
			cout << "\n";
			cout << "Arvore binaria gerada:\n";
			cout << "\n";

			gerar_arvore_completa(&raiz, n);
			mostrar_arvore(raiz);

			cout << "Pre-order:\n";

			imprimir_preorder(raiz);

			cout << "\n\n";
			cout << "In-order:\n";

			imprimir_inorder(raiz);

			cout << "\n\n";
			cout << "Post-order:\n";

			imprimir_postorder(raiz);

			cout << "\n\n";
			
			break;

		case 2:
			cout << "Digite a quantidade de elementos da arvore binaria completa: ";
			cin >> n;
			cout << "\n";
			cout << "Arvore binaria gerada:\n";
			cout << "\n";

			gerar_arvore_randomica(&raiz, n);
			mostrar_arvore(raiz);

			cout << "Pre-order:\n";

			imprimir_preorder(raiz);

			cout << "\n\n";
			cout << "In-order:\n";

			imprimir_inorder(raiz);

			cout << "\n\n";
			cout << "Post-order:\n";

			imprimir_postorder(raiz);

			cout << "\n\n";

			break;

		}
	} while (opcao != 3);
}