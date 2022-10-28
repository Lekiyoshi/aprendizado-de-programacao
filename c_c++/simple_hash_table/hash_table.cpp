#include <iostream>
#include <cstdlib>
#include <cmath>
#include "hash_table.h"

using namespace std;

// construtor
TabelaHash::TabelaHash() {
	for (int i = 0; i < MAX_TABELA_HASH; i++) {
		baldes[i] = NULL;	// inicializa o vetor que representa a tabela hash com NULL
	}
}

// função hash
int TabelaHash::f_hash(int c) {
	return (int)abs(c % MAX_TABELA_HASH);	// retorna o valor absoluto do resto da divisão de 'c' por 10, resultando entre 0 a 9
}

// método para inserir uma chave em um novo registro da tabela hash
void TabelaHash::inserir(int a, int b) {
	int index = f_hash(a);	// chama a função hash da chave 'a' e armazena o resultado, usado para identificar o slot/balde que vai receber a chave

	Registro* temp = baldes[index];		// cria ponteiro para auxiliar no atravessamento da lista do balde

	if (baldes[index] != NULL) {	// se já existe pelo menos um registro no balde

		while (temp != NULL) {	// enquanto 'temp' apontar para um registro
			if (temp->chave == a) {	// se esse registro contém a mesma chave a ser inserida
				return;				// retorna, pois não será necessário adicionar a chave novamente
			}

			if (temp->proximo == NULL) {	// se não houver um próximo registro
				break;						// sai do laço de repetição
			}

			temp = temp->proximo;	// faz 'temp' apontar para o próximo registro e o laço se repete até encontrar o último
		}
	}

	Registro* novo = new Registro;	// ponteiro para alocar memória para o novo registro

	novo->chave = a;		// a chave do novo registro recebe o valor de 'a'
	novo->valor = b;		// o valor do novo registro recebe o valor de 'b'
	novo->proximo = NULL;	// ponteiro 'proximo' do novo registro aponta para NULL, porque será o último na lista do balde

	if (baldes[index] == NULL) {	// se o balde está vazio
		baldes[index] = novo;		// insere o novo registro com o
	}
	else {
		temp->proximo = novo;	// faz 'proximo' do último registro da lista apontar para o novo registro
	}
}

// método para imprimir a tabela hash com todos os seus registros
void TabelaHash::mostrar() {
	Registro* temp;		// ponteiro para auxiliar na travessia da lista encadeada em cada balde da tabela hash

	for (int i = 0; i < MAX_TABELA_HASH; i++) {
		cout << "| ";
		cout.width(2); cout << right << i;	// imprime o índice da tabela hash
		cout << " |";

		if (baldes[i] == NULL) {	// se não há registros inseridos no balde indicado pelo índice, não há nada para imprimir 
			cout << "\n";			// quebra de linha
			continue;				// e continua para o próximo balde
		}

		temp = baldes[i];	// faz 'temp' apontar para o primeiro registro do balde

		while (temp != NULL) {	// até 'temp' apontar para NULL, imprime a chave do registro apontado atualmente
			cout << " --> ";
			cout.width(2); cout << right << temp->chave;
			temp = temp->proximo;	// faz 'temp' apontar para o próximo registro e repete o laço
		}

		cout << "\n";	// quebra de linha e passa para o próximo balde
	}
}

// método para localizar uma chave específica na tabela hash
void TabelaHash::localizar(int a) {
	int index = f_hash(a);		// chama a função hash do valor de 'a' e armazena o resultado
	int contador_registros = 0;	// variável para enumerar os registros

	Registro* temp = baldes[index];		// ponteiro para auxiliar na travessia da lista encadeada do balde

	while (temp != NULL) {	// enquanto 'temp' estiver apontando para um registro
		contador_registros++;	// incrementa o contador de registros

		if (temp->chave == a) {	// se o registro contém a chave, imprime mensagem confirmando a localização
			cout << "Chave " << a << " encontrada no indice " << index << " da tabela hash, no " << contador_registros << "o registro do balde.\n";
			cout << "Valor do registro: " << temp->valor << "\n";

			return;		// retorna
		}

		temp = temp->proximo;	// faz 'temp' apontar para o próximo registro
	}

	cout << "Chave " << a << " nao encontrada na tabela hash.\n";
}