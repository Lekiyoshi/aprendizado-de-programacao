/**
 * @file kn_matrizes.cpp
 * @author Levi Kiyoshi
 * @brief Programa para soma e multiplicação de matrizes aleatórias
 */

#include <iostream>
#include <iomanip>

using namespace std;

// Criação da classe para representação de uma matriz
class Matriz {
    private:
        // Variáveis que armazenarão as dimensões da matriz e a matriz em si
        int linhas;
        int colunas;
        int **matriz = nullptr;
        
    public:
        // Construtor da classe
        Matriz(int a, int b) {  // Recebe como argumentos apenas as quantidades de linhas e colunas
            linhas = a;
            colunas = b;
            
            matriz = new int*[a];  // Alocação de memória para a matriz
            for (int i = 0; i < a; i++) {
                matriz[i] = new int[b];
            }
            
            // Preenchimento da matriz com números aleatórios
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < b; j++) {
                    matriz[i][j] = rand() % 21 + (-10);  // Números inteiros de -10 a 10
                }
            }
        }
        
        // Construtor alternativo
        // Além das dimensões, recebe o endereço de uma matriz que já foi criada
        // As dimensões ainda precisam ser passadas e estarem em conformidade 
        // com a matriz para manter o funcionamento correto das operações
        Matriz(int a, int b, int** matriz) {
            linhas = a;
            colunas = b;
            this->matriz = matriz;
        }
        
        // Getters para obter os dados das variáveis da classe, que são privadas
        int getLinhas() {
            return linhas;
        }
        
        int getColunas() {
            return colunas;
        }
        
        int getElemento(int i, int j) {
            return matriz[i][j];
        }
        
        // Método para soma de matrizes
        Matriz* Soma(Matriz matriz2) {
            // A matriz da própria instância da classe será somada com a matriz de outra
            // instância ('matriz2'), passada como argumento na chamada da função
            
            // A soma será possível apenas com matrizes de dimensões iguais
            // Caso as matrizes sejam incompatíveis, ocorrerá uma excessão e a operação não será realizada
            if (this->linhas != matriz2.getLinhas() || this->colunas != matriz2.getColunas()) {
                throw "A soma das matrizes nao e possivel.";
            }
            
            // Alocação de memória para a matriz resultado
            int **resultado = new int*[linhas];
            for (int i = 0; i < linhas; i++) {
                resultado[i] = new int[colunas];
            }
            
            // Soma das matrizes
            for (int i = 0; i < linhas; i++) {
                for (int j = 0; j < colunas; j++) {
                    resultado[i][j] = matriz[i][j] + matriz2.getElemento(i, j);
                }
            }
            
            // Cria um objeto da classe Matriz para armazenar o resultado
            Matriz *resultadoMatriz = new Matriz(linhas, colunas, resultado);
            
            return resultadoMatriz;
        }
        
        // Método para multiplicação de matrizes
        Matriz* Produto(Matriz matriz2) {
            // A multiplicação será possível apenas se o número de colunas da matriz 1 for igual ao de linhas da matriz 2
            // Caso as matrizes sejam incompatíveis, ocorrerá uma excessão e a operação não será realizada
            if (this->colunas != matriz2.getLinhas()) {
                throw "O produto das matrizes nao e possivel.";
            }
            
            // Alocação de memória para a matriz resultado
            int **resultado = new int*[linhas];
            for (int i = 0; i < linhas; i++) {
                resultado[i] = new int[matriz2.getColunas()];
                for (int j = 0; j < matriz2.getColunas(); j++) {
                    resultado[i][j] = 0;
                }
            }
            
            // Multiplicação das matrizes
            for (int i = 0; i < linhas; i++) {
                for (int j = 0; j < matriz2.getColunas(); j++) {
                    for (int k = 0; k < colunas; k++) {
                        resultado[i][j] += matriz[i][k] * matriz2.getElemento(k, j);
                    }
                }
            }
            
            // Cria um objeto da classe Matriz para armazenar o resultado
            Matriz *resultadoMatriz = new Matriz(linhas, matriz2.getColunas(), resultado);
            
            return resultadoMatriz;
        }
        
        // Método para imprimir os elementos da matriz
        void imprimirMatriz() {
            for (int i = 0; i < linhas; i++) {
                for (int j = 0; j < colunas; j++) {
                    cout << setw(6);
                    cout << matriz[i][j];
                }
                
                cout << "\n";
            }
        }
    
};

int main() {
    int m, n, o, p;  // Variáveis para as dimensões das matrizes
    
    cout << "Informe o numero de linhas da matriz A: ";
    cin >> m;
    cout << "Informe o numero de colunas da matriz A: ";
    cin >> n;
    cout << "Informe o numero de linhas da matriz B: ";
    cin >> o;
    cout << "Informe o numero de colunas da matriz B: ";
    cin >> p;
    
    // Criação das duas matrizes com as dimensões especificadas
    Matriz *matrizA = new Matriz(m, n);
    Matriz *matrizB = new Matriz(o, p);
    Matriz *resultado = nullptr;
    
    // Visualização das duas matrizes
    cout << "\nMatriz A: \n";
    matrizA->imprimirMatriz();
    cout << "\nMatriz B: \n";
    matrizB->imprimirMatriz();
    
    // Soma (A+B)
    cout << "\nA + B\n";
    try {
        resultado = matrizA->Soma(*matrizB);
        resultado->imprimirMatriz();
        delete resultado;
    } catch (const char* msg) {
        cerr << msg << "\n";
    }
    
    // Produtos (AB e BA)
    cout << "\nA * B\n";
    try {
        resultado = matrizA->Produto(*matrizB);
        resultado->imprimirMatriz();
        delete resultado;
    } catch (const char* msg) {
        cerr << msg << "\n";
    }
    
    cout << "\nB * A\n";
    try {
        resultado = matrizB->Produto(*matrizA);
        resultado->imprimirMatriz();
        delete resultado;
    } catch (const char* msg) {
        cerr << msg << "\n";
    }
    cout << "\n";
    
    system("pause");
    
    return 0;
}