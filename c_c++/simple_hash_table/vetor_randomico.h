#pragma once

class VetorRandomico {	// classe para gerar um vetor de números inteiros aleatórios
private:
	int tamanho;	// irá armazenar o tamanho do vetor
	int* vetor;		// ponteiro para o vetor a ser criado

public:
	VetorRandomico(int, int);
	int obter_valor(int);
	int obter_tamanho();
	void localizar(int);
};