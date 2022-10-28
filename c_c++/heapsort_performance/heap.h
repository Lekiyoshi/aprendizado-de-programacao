#pragma once

class MaxHeap {
private:
	int heap[10000];	// um vetor para representar o heap
	int tamanho;		// o tamanho indica o índice do último elemento no heap e aumenta a cada elemento inserido

public:
	MaxHeap();
	int pai(int);
	int filho_esquerdo(int);
	int filho_direito(int);
	void subir(int);
	void descer(int);
	void inserir(int);
	int extrair_max();
	void mudar_prioridade(int, int);
	void construir_heap_com_subir();
	void construir_heap_com_descer();
	void heapsort();
	void bubble_sort();
	void randomizar_vetor(int);
};
