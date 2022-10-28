#pragma once

class Node {
public:
	int dado;
	Node* esquerdo;
	Node* direito;

	Node();
};

void crescer_folha(Node**);

void gerar_arvore_randomica(Node**, int);

void gerar_arvore_completa(Node**, int);

void deletar_arvore(Node*);

int obter_altura(Node*);

void imprimir_nivel(Node*, int, int);

void mostrar_arvore(Node*);

void imprimir_preorder(Node*);

void imprimir_inorder(Node*);

void imprimir_postorder(Node*);
