#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include "binary_tree.h"

using namespace std;

// construtor de um n�
Node::Node() {
	dado = rand() % 100;		// inicia com um valor aleat�rio de 0 a 99
	esquerdo = direito = NULL;	// ponteiros 'esquerdo' e 'direito' iniciam com NULL
}

// fun��o para criar um n�/folha usando um ponteiro
void crescer_folha(Node** ponteiro) {
	if (*ponteiro != NULL) {	// se esse ponteiro j� aponta para um n�
		return;					// n�o ser� preciso criar outro
	}
	else {						// caso contr�rio
		*ponteiro = new Node;	// um novo n� � criado para o ponteiro
	}
}

// fun��o para gerar uma �rvore bin�ria com ramifica��es randomizadas a partir de um ponteiro
void gerar_arvore_randomica(Node** raiz, int n) {
	if (*raiz != NULL) {		// se o ponteiro da raiz j� tem um n�
		deletar_arvore(*raiz);	// deleta esse n� e suas sub�rvores
		*raiz = NULL;			// muda o ponteiro da raiz para NULL
	}

	Node* temp;				// ponteiro para auxiliar na travessia
	int seletor_caminho;	// vari�vel para auxiliar na escolha do caminho a ser atravessado

	crescer_folha(raiz);	// insere um novo n� no ponteiro da raiz

	// la�o de repeti��o para inserir um n�, sendo a quantidade de n�s definida pelo par�metro 'n'
	for (int i = 0; i < n-1; i++) {
		temp = *raiz;	// faz 'temp' apontar para o n� da raiz sempre que iniciar uma nova itera��o

		// la�o de repeti��o para fazer 'temp' percorrer da raiz at� encontrar um ponteiro vazio
		while (temp != NULL) {
			seletor_caminho = rand() % 2;	// gerar 0 ou 1 para selecionar o caminho

			if (seletor_caminho == 0) {				// se gerar 0, escolhe o caminho esquerdo
				if (temp->esquerdo == NULL) {		// se o ponteiro esquerdo for NULL
					crescer_folha(&temp->esquerdo);	// insere um novo n�
					break;							// e finaliza o la�o de repeti��o
				}
				temp = temp->esquerdo;	// caso o ponteiro esquerdo j� tenha um n�, ainda devemos caminhar um pouco mais
			}
			else {									// se gerar 1, escolhe o caminho direito
				if (temp->direito == NULL) {		// se o ponteiro direito for NULL
					crescer_folha(&temp->direito);	// insere um novo n�
					break;							// e finaliza o la�o de repeti��o
				}
				temp = temp->direito;	// caso o ponteiro direito j� tenha um n�, ainda devemos caminhar um pouco mais
			}
		}
	}
}

// fun��o para gerar uma �rvore bin�ria completa a partir de um ponteiro
void gerar_arvore_completa(Node** raiz, int n) {
	if (*raiz != NULL) {		// se o ponteiro da raiz j� tem um n�
		deletar_arvore(*raiz);	// deleta esse n� e suas sub�rvores
		*raiz = NULL;			// muda o ponteiro da raiz para NULL
	}

	Node** temp = new Node*[n];		// cria um vetor de ponteiros para auxiliar na cria��o individual dos n�s

	for (int i = 0; i < n; i++) {
		temp[i] = new Node;		// cria um n� para cada ponteiro do vetor 'temp'
	}

	*raiz = temp[0];	// faz o ponteiro da raiz apontar para o primeiro n� do vetor 'temp'

	// la�o de repeti��o para ajuste dos ponteiros esquerdo e direito dos n�s
	for (int i = 0; i < (int)(n / 2); i++) {	// esse ajuste � feito at� o �ltimo n� que n�o � folha (n/2)
		temp[i]->esquerdo = temp[2 * i + 1];	// ajusta o ponteiro esquerdo

		if (2 * i + 2 < n) {					// � preciso verificar se o tamanho do vetor permite uma sub�rvore direita
			temp[i]->direito = temp[2 * i + 2];	// caso verdadeiro, ajusta o ponteiro direito
		}
	}

	delete[] temp;	// libera a mem�ria ocupada pelos ponteiros auxiliares
}

// fun��o para libera��o de mem�ria de uma �rvore bin�ria
void deletar_arvore(Node* raiz) {
	if (raiz == NULL) {	// se n�o houver uma raiz
		return;			// ent�o n�o h� nada para deletar
	}

	deletar_arvore(raiz->esquerdo);	// chama a fun��o recursivamente para deletar as sub�rvores
	deletar_arvore(raiz->direito);	// de ambos os lados

	delete raiz;	// deleta o n� na raiz
}

// fun��o para obter a altura de uma �rvore bin�ria atrav�s do ponteiro para sua raiz
int  obter_altura(Node* raiz) {
	if (raiz == NULL) {	// se n�o houver uma raiz
		return 0;		// ent�o n�o h� arvore (esse � o caso base)
	}
	else {
		int altura_esquerda = obter_altura(raiz->esquerdo);	// chama a fun��o recursivamente para obter a altura da sub�rvore esquerda
		int altura_direita = obter_altura(raiz->direito);	// o mesmo para o lado direito

		if (altura_esquerda > altura_direita) {	// compara as alturas de ambas as sub�rvores e retorna aquela que for maior
			return altura_esquerda + 1;			// adiciona-se 1 para cada n�vel da �rvore encontrado
		}
		else {
			return altura_direita + 1;
		}
	}
}

// fun��o para imprimir um n�vel espec�fico de uma �rvore bin�ria
void imprimir_nivel(Node* raiz, int r, int h) {
	int recuo = 6 * (int)pow(2, h - r - 1) - 3;	// calcula o recuo que cada n�vel ter�, baseado na altura da �rvore
												// isso � necess�rio para manter todos os n�s nas posi��es corretas quando a fun��o 'mostrar_arvore' for chamada

	if (raiz == NULL) {		// caso base, imprime os espa�os vazios do n�vel, baseado em quantos n�veis faltam para a fun��o chegar na base da �rvore
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

	if (r == 1) {	// caso 'r' seja 1, j� estamos no n�vel desejado e o valor do n� visitado � impresso ap�s o devido recuo
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
	else if (r > 1) {	// caso 'r' seja maior que 1, ainda n�o estamos no n�vel desejado
		imprimir_nivel(raiz->esquerdo, r - 1, h - 1);	// e a fun��o � chamada recursivamente para cada sub�rvore
		imprimir_nivel(raiz->direito, r - 1, h - 1);	// at� encontrar o n�vel a ser impresso
	}
}

// fun��o para imprimir todos os n�veis da �rvore bin�ria
void mostrar_arvore(Node* raiz) {
	int h = obter_altura(raiz);		// obt�m a altura da �rvore para passar como par�metro

	for (int i = 1; i <= h; i++) {	// intera��o pela quantidade de n�veis, determinada pela altura
		imprimir_nivel(raiz, i, h);
		cout << "\n\n";
	}
}

// fun��o para imprimir �rvore bin�ria em pre-order
void imprimir_preorder(Node* raiz) {
	if (raiz == NULL) {
		return;
	}

	cout << raiz->dado << " ";
	imprimir_preorder(raiz->esquerdo);
	imprimir_preorder(raiz->direito);
}

// fun��o para imprimir �rvore bin�ria in-order
void imprimir_inorder(Node* raiz) {
	if (raiz == NULL) {
		return;
	}

	imprimir_inorder(raiz->esquerdo);
	cout << raiz->dado << " ";
	imprimir_inorder(raiz->direito);
}

// fun��o para imprimir �rvore bin�ria em post-order
void imprimir_postorder(Node* raiz) {
	if (raiz == NULL) {
		return;
	}

	imprimir_postorder(raiz->esquerdo);
	imprimir_postorder(raiz->direito);
	cout << raiz->dado << " ";
}