#pragma once

#define MAX_TABELA_HASH 10

class Registro {	// classe para um registro da tabela hash, com adapta��o para o endere�amento fechado
public:
	int chave;	// chave armazenada
	int valor;	// valor associado � chave
	Registro* proximo;	// ponteiro para o pr�ximo registro
};

class TabelaHash {	// classe da tabela hash
	private:
		Registro* baldes[MAX_TABELA_HASH];	// a tabela hash ter� 10 slots/baldes de registros

	public:
		TabelaHash();		// construtor
		int f_hash(int);	// fun��o hash
		void inserir(int, int);	// inserir registro na tabela hash
		void mostrar();			// mostrar tabela hash
		void localizar(int);	// mostrar a posi��o de uma chave j� inserida e seu valor
};