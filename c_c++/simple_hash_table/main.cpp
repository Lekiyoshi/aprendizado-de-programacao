// Trabalho II de Estrutura de Dados I
// Implementação e uso de tabela hash com função hash h(c) = c mod 10
// Escrito por LeviK

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include "hash_table.h"
#include "vetor_randomico.h"

using namespace std;

int main() {
	TabelaHash tabela_hash;
	VetorRandomico* vetor_a = NULL;
	int opcao_menu;
	int a1, a2, b;

	srand(time(NULL));

	do {
		cout << "+ - - - - - - - - - - - - - - MENU - - - - - - - - - - - - - - +\n";
		cout << "| 1. Criar vetor A com chaves randomizadas                     |\n";
		cout << "| 2. Armazenar chaves do vetor A na tabela hash                |\n";
		cout << "| 3. Mostrar a tabela hash                                     |\n";
		cout << "| 4. Solicitar uma chave e seu valor na tabela hash            |\n";
		cout << "| 5. Sair                                                      |\n";
		cout << "+ - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - +\n";

		cout << "\n";
		cout << "Escolha uma opcao: ";
		cin >> opcao_menu;
		cout << "\n";

		switch (opcao_menu) {
		case 1:
			if (vetor_a != NULL) {	// caso já exista um vetor
				break;				// não será criado outro
			}

			cout << "Digite o tamanho do vetor A: ";
			cin >> a1;
			cout << "Digite o limite maximo dos numeros aleatorios: ";
			cin >> a2;
			cout << "\n";

			vetor_a = new VetorRandomico(a1, a2);	// cria o vetor no ponteiro 'vetor_a', com os parâmetros especificados

			break;

		case 2:
			if (vetor_a == NULL) {	// verifica se um vetor já foi criado
				cout << "O vetor A ainda nao foi criado.\n";
				
				break;	// se não foi criado, não há nada para armazenar na tabela hash
			}
			
			for (int i = 0; i < vetor_a->obter_tamanho(); i++) {	// caso o vetor exista, faz uma varredura desse vetor
				tabela_hash.inserir(vetor_a->obter_valor(i), i);	// inserindo suas chaves e seus respectivos índices como valores dos registros na tabela hash
			}

			cout << "Chaves do vetor A foram inseridos na tabela hash.\n";
			cout << "\n";

			tabela_hash.mostrar();	// imprime a tabela hash com todos os baldes de registros

			break;

		case 3:
			tabela_hash.mostrar();	// imprime a tabela hash com todos os baldes de registros

			break;

		case 4:
			cout << "Digite o valor de uma chave a ser procurada na tabela hash: ";
			cin >> b;
			cout << "\n";

			tabela_hash.localizar(b);	// verifica se a chave está na tabela hash e, se verdadeiro, imprime a sua localização e seu valor associado

			break;
		}

		cout << "\n";
	} while (opcao_menu != 5);
}