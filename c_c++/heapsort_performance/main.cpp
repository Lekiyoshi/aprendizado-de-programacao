/**
 * Construção de heaps, com teste de velocidade 
 * Escrito por Lekiyoshi
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cmath>
#include "heap.h"

using namespace std;

int main() {
	fstream resultados;
	MaxHeap heap;

	srand(time(NULL));

	resultados.open("grafico_performance.csv", ios::out | ios::trunc);	// os resultados serão escritos em microsegundos, em um arquivo de valores separados por vírgula
																		// para uso em programas de planilha como Microsoft Excel e LibreOffice Calc
	resultados << ",";

	for (int a = 0; a <= 10000; a += 50) {
		resultados << a << ",";		// escreve os rótulos de cada coluna no arquivo .csv
	}

	resultados << "\nSubir de 2 até n,";	// quebra de linha e rótulo da próxima linha

	for (int a = 0; a <= 10000; a += 50) {
		heap.randomizar_vetor(a);	// randomiza o vetor a cada repetição

		auto inicio = chrono::steady_clock::now();	// registra o início
		heap.construir_heap_com_subir();			// constroi o heap com subidas usadas do elemento 2 até n (complexidade: O(n log n))
		auto fim = chrono::steady_clock::now();		// registra o final

		resultados << chrono::duration_cast<chrono::microseconds>(fim - inicio).count() << ",";    // escreve os resultados no arquivo .csv
	}

	resultados << "\nDescer de n/2 até 1,";		// quebra de linha e rótulo da próxima linha

	for (int a = 0; a <= 10000; a += 50) {
		heap.randomizar_vetor(a);

		auto inicio = chrono::steady_clock::now();	// registra o início
		heap.construir_heap_com_descer();			// constroi o heap com operações de descida usadas do elemento 2 até n (complexidade: O(n))
		auto fim = chrono::steady_clock::now();		// registra o final

		resultados << chrono::duration_cast<chrono::microseconds>(fim - inicio).count() << ",";    // escreve os resultados no arquivo .csv
	}

	resultados << "\nHeapsort,";	// quebra de linha e rótulo da próxima linha

	for (int a = 0; a <= 10000; a += 50) {
		heap.randomizar_vetor(a);

		auto inicio = chrono::steady_clock::now();	// registra o início
		heap.heapsort();							// heapsort (complexidade: O(n log n))
		auto fim = chrono::steady_clock::now();		// registra o final

		resultados << chrono::duration_cast<chrono::microseconds>(fim - inicio).count() << ",";    // escreve os resultados no arquivo .csv
	}

	resultados << "\nBubble sort,";		// quebra de linha e rótulo da próxima linha

	for (int a = 0; a <= 300; a += 50) {
		heap.randomizar_vetor(a);

		auto inicio = chrono::steady_clock::now();	// registra o início
		heap.bubble_sort();							// "constroi o heap" através de ordenação comum (complexidade: O(n^2))
		auto fim = chrono::steady_clock::now();		// registra o final

		resultados << chrono::duration_cast<chrono::microseconds>(fim - inicio).count() << ",";    // escreve os resultados no arquivo .csv
	}

	resultados.close();
}