#pragma once

#define MAX_TABELA_HASH 10

class Registro {	// classe para um registro da tabela hash, com adaptação para o endereçamento fechado
public:
	int chave;	// chave armazenada
	int valor;	// valor associado à chave
	Registro* proximo;	// ponteiro para o próximo registro
};

class TabelaHash {	// classe da tabela hash
	private:
		Registro* baldes[MAX_TABELA_HASH];	// a tabela hash terá 10 slots/baldes de registros

	public:
		TabelaHash();		// construtor
		int f_hash(int);	// função hash
		void inserir(int, int);	// inserir registro na tabela hash
		void mostrar();			// mostrar tabela hash
		void localizar(int);	// mostrar a posição de uma chave já inserida e seu valor
};