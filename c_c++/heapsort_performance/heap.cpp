#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "heap.h"

using namespace std;

// construtor para inicializar o heap e seu tamanho
MaxHeap::MaxHeap() {
	for (int i = 0; i < 10000; i++) {
		heap[i] = NULL;
	}
	
	tamanho = 0;	// indica a quantidade de elementos inseridos
}

// fun��o para obter o �ndice do pai de um elemento
int MaxHeap::pai(int i) {
	return (i - 1) / 2;
}

// fun��o para obter o �ndice do filho esquerdo de um elemento
int MaxHeap::filho_esquerdo(int i) {
	return ((2 * i) + 1);
}

// fun��o para obter o �ndice do filho direito de um elemento
int MaxHeap::filho_direito(int i) {
	return ((2 * i) + 2);
}

// fun��o para fazer um elemento subir para manter a propriedade de heap
void MaxHeap::subir(int i) {
	if (i > 0 && heap[pai(i)] < heap[i]) {	// verifica se um pai existe
		swap(heap[pai(i)], heap[i]);	// troca o elemento com seu pai caso o pai seja menor

		subir(pai(i));	// faz a subida do pai recursivamente se necess�rio
	}
}

// fun��o para fazer um elemento descer para manter a propriedade de heap
void MaxHeap::descer(int i) {
	int max_i = i;	// vari�vel para armazenar o �ndice do maior elemento, iniciando com 'i'

	int l = filho_esquerdo(i);	// filho esquerdo do elemento

	if (l < tamanho && heap[l] > heap[max_i]) {	// verifica se o filho esquerdo est� dentro do heap e faz uma compara��o para ver qual � o maior
		max_i = l;	// caso verdadeiro, atualiza 'max_i' com o �ndice do filho esquerdo
	}

	int r = filho_direito(i);	// filho direito do elemento

	if (r < tamanho && heap[r] > heap[max_i]) {	// verifica se o filho direito est� dentro do heap e faz uma compara��o para ver qual � o maior
		max_i = r;	// caso verdadeiro, atualiza 'max_i' com o �ndice do filho direito
	}

	if (i != max_i) {				// caso 'i' seja diferente de 'max_i' (quando 'max_i' foi atualizado com o �ndice de um dos filhos)
		swap(heap[i], heap[max_i]);	// faz a troca entre o elemento e seu filho maior
		descer(max_i);				// faz a descida do filho que foi trocado se necess�rio para restabelecer a propriedade de heap
	}
}

// fun��o para inserir novo elemento no heap
void MaxHeap::inserir(int p) {
	heap[tamanho] = p;		// insere o novo elemento no final do heap, indicado pelo atual do tamanho
	tamanho++;				// atualiza o tamanho do heap
	subir(tamanho - 1);		// faz a subida desse elemento para restabelecer a propriedade de heap
}

// fun��o para extrair o elemento de prioridade maior (o que est� no in�cio do heap)
int MaxHeap::extrair_max() {
	int max = heap[0];	// armazena o elemento no in�cio do heap em uma vari�vel

	heap[0] = heap[tamanho - 1];	// insere o �ltimo elemento do heap no in�cio
	tamanho--;						// atualiza o tamanho do heap

	descer(0);	// faz a descida desse elemento para restabelecer a propriedade de heap

	return max;	// retorna o elemento que estava no in�cio do heap
}

// fun��o para mudar a prioridade/valor de um elemento
void MaxHeap::mudar_prioridade(int i, int p) {
	int oldp = heap[i];	// armazena a prioridade a ser substitu�da em uma vari�vel
	heap[i] = p;		// e atribui a nova prioridade no elemento

	if (p > oldp) {		// se essa nova prioridade for maior que a velha
		subir(i);		// faz sua subida para restabelecer a propriedade de heap se necess�rio
	}
	else {				// caso contr�rio
		descer(i);		// faz a descida para restabelecer a propriedade de heap se necess�rio
	}
}

// constroi o heap a partir do vetor, com opera��es de subida usadas do elemento 2 at� n (complexidade: O(n log n))
void MaxHeap::construir_heap_com_subir() {
	for (int i = 1; i < tamanho; i++) {
		subir(i);
	}
}

// constroi o heap a partir do vetor, com opera��es de descida usadas do elemento n/2 at� 1 (complexidade: O(n))
void MaxHeap::construir_heap_com_descer() {
	for (int i = tamanho/2; i >= 0; i--) {	// o elemento na posi��o n/2 � usado pois esse � o �ltimo elemento com filhos no heap
		descer(i);
	}
}

// heapsort (complexidade: O(n log n))
void MaxHeap::heapsort() {
	construir_heap_com_descer();	// primeira etapa � construir o heap com descidas

	for (int i = tamanho - 1; i > 0; i--) {
		swap(heap[0], heap[tamanho - 1]);	// troca o primeiro elemento com o �ltimo

		tamanho--;	// diminui o tamanho, excluindo o �ltimo elemento

		descer(0);	// faz a descida do elemento que foi para o in�cio do heap
	}
}

// algoritmo de ordena��o comun baseado em compara��es, � extremamente lento (complexidade: O(n^2))
void MaxHeap::bubble_sort() {
	for (int n = tamanho; n > 0; n--) {
		for (int i = 1; i < tamanho; i++) {
			if (heap[i] > heap[i - 1]) {
				swap(heap[i], heap[i - 1]);
			}
		}
	}
}

// fun��o para inserir elementos aleat�rios no vetor at� que tenha o tamanho especificado
void MaxHeap::randomizar_vetor(int n) {
	tamanho = n;	// muda o tamanho do heap

	for (int i = 0; i < n; i++) {
		heap[i] = rand() % 10000 + 1;	// insere elemento aleat�rios de 1 a 10000 at� o �ndice especificado
	}
}