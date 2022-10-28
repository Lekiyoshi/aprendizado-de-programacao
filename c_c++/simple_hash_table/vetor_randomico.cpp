#include <iostream>
#include <cstdlib>
#include <cmath>
#include "vetor_randomico.h"

using namespace std;

// construtor
VetorRandomico::VetorRandomico(int a, int b) {	// recebe como parâmetros o tamanho do vetor e o limite máximo de seus números aleatórios
	tamanho = a;
	vetor = new int[tamanho];

	for (int i = 0; i < tamanho; i++) {		// gera os números aleatórios para cada índice do vetor
		vetor[i] = rand() % b;
	}

	cout << "Vetor criado:\n";

	for (int i = 0; i < tamanho; i++) {		// imprime o vetor gerado
		cout << "| ";
		cout.width(3); cout << vetor[i];
		cout << " ";
	}
	cout << "|\n";
}

// método para obter o número armazenado na posição especificada
int VetorRandomico::obter_valor(int index) {
	if (index > tamanho - 1) {	// verifica se o índice passado como parâmetro faz parte do vetor
		cout << "O indice excede o tamanho do vetor.\n";

		return -1;
	}

	return vetor[index];
}

// método para obter o tamanho do vetor atual
int VetorRandomico::obter_tamanho() {
	return tamanho;
}

// método para identificar a posição ou as posições de um valor já inserido no vetor
void VetorRandomico::localizar(int valor) {
	int qt_encontrados = 0;		// contador para caso o valor a ser procurado tenha mais de uma instância no vetor

	for (int i = 0; i < tamanho; i++) {
		if (vetor[i] == valor) {
			if (qt_encontrados == 0) {
				cout << valor << " encontrado no(s) indice(s) " << i;	// imprime o primeiro índice do vetor que contém o valor procurado
			}
			else {
				cout << ", " << i;	// e outros índices adicionais, caso também contenham o valor
			}

			qt_encontrados++;	// aumenta o contador para cada encontro
		}
	}

	if (qt_encontrados == 0) {	// caso o valor não tenha sido encontrado, avisa que não foi encontrado
		cout << valor << " nao foi encontrado no vetor.\n";
	}
	else {
		cout << " do vetor.\n";
	}
}