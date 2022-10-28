#pragma once

class VetorRandomico {	// classe para gerar um vetor de n�meros inteiros aleat�rios
private:
	int tamanho;	// ir� armazenar o tamanho do vetor
	int* vetor;		// ponteiro para o vetor a ser criado

public:
	VetorRandomico(int, int);
	int obter_valor(int);
	int obter_tamanho();
	void localizar(int);
};