#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include "binary_tree.h"

using namespace std;

// construtor de um nó
Node::Node() {
	dado = rand() % 100;		// inicia com um valor aleatório de 0 a 99
	esquerdo = direito = NULL;	// ponteiros 'esquerdo' e 'direito' iniciam com NULL
}

// função para criar um nó/folha usando um ponteiro
void crescer_folha(Node** ponteiro) {
	if (*ponteiro != NULL) {	// se esse ponteiro já aponta para um nó
		return;					// não será preciso criar outro
	}
	else {						// caso contrário
		*ponteiro = new Node;	// um novo nó é criado para o ponteiro
	}
}

// função para gerar uma árvore binária com ramificações randomizadas a partir de um ponteiro
void gerar_arvore_randomica(Node** raiz, int n) {
	if (*raiz != NULL) {		// se o ponteiro da raiz já tem um nó
		deletar_arvore(*raiz);	// deleta esse nó e suas subárvores
		*raiz = NULL;			// muda o ponteiro da raiz para NULL
	}

	Node* temp;				// ponteiro para auxiliar na travessia
	int seletor_caminho;	// variável para auxiliar na escolha do caminho a ser atravessado

	crescer_folha(raiz);	// insere um novo nó no ponteiro da raiz

	// laço de repetição para inserir um nó, sendo a quantidade de nós definida pelo parâmetro 'n'
	for (int i = 0; i < n-1; i++) {
		temp = *raiz;	// faz 'temp' apontar para o nó da raiz sempre que iniciar uma nova iteração

		// laço de repetição para fazer 'temp' percorrer da raiz até encontrar um ponteiro vazio
		while (temp != NULL) {
			seletor_caminho = rand() % 2;	// gerar 0 ou 1 para selecionar o caminho

			if (seletor_caminho == 0) {				// se gerar 0, escolhe o caminho esquerdo
				if (temp->esquerdo == NULL) {		// se o ponteiro esquerdo for NULL
					crescer_folha(&temp->esquerdo);	// insere um novo nó
					break;							// e finaliza o laço de repetição
				}
				temp = temp->esquerdo;	// caso o ponteiro esquerdo já tenha um nó, ainda devemos caminhar um pouco mais
			}
			else {									// se gerar 1, escolhe o caminho direito
				if (temp->direito == NULL) {		// se o ponteiro direito for NULL
					crescer_folha(&temp->direito);	// insere um novo nó
					break;							// e finaliza o laço de repetição
				}
				temp = temp->direito;	// caso o ponteiro direito já tenha um nó, ainda devemos caminhar um pouco mais
			}
		}
	}
}

// função para gerar uma árvore binária completa a partir de um ponteiro
void gerar_arvore_completa(Node** raiz, int n) {
	if (*raiz != NULL) {		// se o ponteiro da raiz já tem um nó
		deletar_arvore(*raiz);	// deleta esse nó e suas subárvores
		*raiz = NULL;			// muda o ponteiro da raiz para NULL
	}

	Node** temp = new Node*[n];		// cria um vetor de ponteiros para auxiliar na criação individual dos nós

	for (int i = 0; i < n; i++) {
		temp[i] = new Node;		// cria um nó para cada ponteiro do vetor 'temp'
	}

	*raiz = temp[0];	// faz o ponteiro da raiz apontar para o primeiro nó do vetor 'temp'

	// laço de repetição para ajuste dos ponteiros esquerdo e direito dos nós
	for (int i = 0; i < (int)(n / 2); i++) {	// esse ajuste é feito até o último nó que não é folha (n/2)
		temp[i]->esquerdo = temp[2 * i + 1];	// ajusta o ponteiro esquerdo

		if (2 * i + 2 < n) {					// é preciso verificar se o tamanho do vetor permite uma subárvore direita
			temp[i]->direito = temp[2 * i + 2];	// caso verdadeiro, ajusta o ponteiro direito
		}
	}

	delete[] temp;	// libera a memória ocupada pelos ponteiros auxiliares
}

// função para liberação de memória de uma árvore binária
void deletar_arvore(Node* raiz) {
	if (raiz == NULL) {	// se não houver uma raiz
		return;			// então não há nada para deletar
	}

	deletar_arvore(raiz->esquerdo);	// chama a função recursivamente para deletar as subárvores
	deletar_arvore(raiz->direito);	// de ambos os lados

	delete raiz;	// deleta o nó na raiz
}

// função para obter a altura de uma árvore binária através do ponteiro para sua raiz
int  obter_altura(Node* raiz) {
	if (raiz == NULL) {	// se não houver uma raiz
		return 0;		// então não há arvore (esse é o caso base)
	}
	else {
		int altura_esquerda = obter_altura(raiz->esquerdo);	// chama a função recursivamente para obter a altura da subárvore esquerda
		int altura_direita = obter_altura(raiz->direito);	// o mesmo para o lado direito

		if (altura_esquerda > altura_direita) {	// compara as alturas de ambas as subárvores e retorna aquela que for maior
			return altura_esquerda + 1;			// adiciona-se 1 para cada nível da árvore encontrado
		}
		else {
			return altura_direita + 1;
		}
	}
}

// função para imprimir um nível específico de uma árvore binária
void imprimir_nivel(Node* raiz, int r, int h) {
	int recuo = 6 * (int)pow(2, h - r - 1) - 3;	// calcula o recuo que cada nível terá, baseado na altura da árvore
												// isso é necessário para manter todos os nós nas posições corretas quando a função 'mostrar_arvore' for chamada

	if (raiz == NULL) {		// caso base, imprime os espaços vazios do nível, baseado em quantos níveis faltam para a função chegar na base da árvore
		int niveis_faltantes = (int)pow(2, r - 1);

		for (int i = 0; i < niveis_faltantes; i++) {
			for (int i = 0; i < recuo; i++) {
				cout << "_";
			}

			cout << "_    _";

			for (int i = 0; i < recuo; i++) {
				cout << "_";
			}
		}

		return;
	}

	if (r == 1) {	// caso 'r' seja 1, já estamos no nível desejado e o valor do nó visitado é impresso após o devido recuo
		for (int i = 0; i < recuo; i++) {
			cout << "_";
		}

		cout << "_(";
		cout.width(2); cout << right << raiz->dado;
		cout << ")_";

		for (int i = 0; i < recuo; i++) {
			cout << "_";
		}
	}
	else if (r > 1) {	// caso 'r' seja maior que 1, ainda não estamos no nível desejado
		imprimir_nivel(raiz->esquerdo, r - 1, h - 1);	// e a função é chamada recursivamente para cada subárvore
		imprimir_nivel(raiz->direito, r - 1, h - 1);	// até encontrar o nível a ser impresso
	}
}

// função para imprimir todos os níveis da árvore binária
void mostrar_arvore(Node* raiz) {
	int h = obter_altura(raiz);		// obtém a altura da árvore para passar como parâmetro

	for (int i = 1; i <= h; i++) {	// interação pela quantidade de níveis, determinada pela altura
		imprimir_nivel(raiz, i, h);
		cout << "\n\n";
	}
}

// função para imprimir árvore binária em pre-order
void imprimir_preorder(Node* raiz) {
	if (raiz == NULL) {
		return;
	}

	cout << raiz->dado << " ";
	imprimir_preorder(raiz->esquerdo);
	imprimir_preorder(raiz->direito);
}

// função para imprimir árvore binária in-order
void imprimir_inorder(Node* raiz) {
	if (raiz == NULL) {
		return;
	}

	imprimir_inorder(raiz->esquerdo);
	cout << raiz->dado << " ";
	imprimir_inorder(raiz->direito);
}

// função para imprimir árvore binária em post-order
void imprimir_postorder(Node* raiz) {
	if (raiz == NULL) {
		return;
	}

	imprimir_postorder(raiz->esquerdo);
	imprimir_postorder(raiz->direito);
	cout << raiz->dado << " ";
}