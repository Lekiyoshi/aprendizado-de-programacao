#include <iostream>
#include <cstdlib>
#include <cmath>
#include "vetor_randomico.h"

using namespace std;

// construtor
VetorRandomico::VetorRandomico(int a, int b) {	// recebe como par�metros o tamanho do vetor e o limite m�ximo de seus n�meros aleat�rios
	tamanho = a;
	vetor = new int[tamanho];

	for (int i = 0; i < tamanho; i++) {		// gera os n�meros aleat�rios para cada �ndice do vetor
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

// m�todo para obter o n�mero armazenado na posi��o especificada
int VetorRandomico::obter_valor(int index) {
	if (index > tamanho - 1) {	// verifica se o �ndice passado como par�metro faz parte do vetor
		cout << "O indice excede o tamanho do vetor.\n";

		return -1;
	}

	return vetor[index];
}

// m�todo para obter o tamanho do vetor atual
int VetorRandomico::obter_tamanho() {
	return tamanho;
}

// m�todo para identificar a posi��o ou as posi��es de um valor j� inserido no vetor
void VetorRandomico::localizar(int valor) {
	int qt_encontrados = 0;		// contador para caso o valor a ser procurado tenha mais de uma inst�ncia no vetor

	for (int i = 0; i < tamanho; i++) {
		if (vetor[i] == valor) {
			if (qt_encontrados == 0) {
				cout << valor << " encontrado no(s) indice(s) " << i;	// imprime o primeiro �ndice do vetor que cont�m o valor procurado
			}
			else {
				cout << ", " << i;	// e outros �ndices adicionais, caso tamb�m contenham o valor
			}

			qt_encontrados++;	// aumenta o contador para cada encontro
		}
	}

	if (qt_encontrados == 0) {	// caso o valor n�o tenha sido encontrado, avisa que n�o foi encontrado
		cout << valor << " nao foi encontrado no vetor.\n";
	}
	else {
		cout << " do vetor.\n";
	}
}