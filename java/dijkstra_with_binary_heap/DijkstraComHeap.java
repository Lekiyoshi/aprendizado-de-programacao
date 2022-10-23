/**
 * Algoritmo de Dijkstra implementado com uso de Heap binário
 * Grafo implementado com lista de adjacências
 * Calcula distâncias corretamente apenas com grafos conexos
 */

package edii_grafo_spt;

import java.util.LinkedList;
import java.util.Stack;
import java.util.Scanner;

public class DijkstraComHeap {
    // Classe da aresta, usada na lista de adjacências
    static class Aresta {
        int origem;
        int destino;
        int peso;
        
        // A aresta é construída com os índices dos vértices de origem e destino e um peso
        public Aresta(int origem, int destino, int peso) {
            this.origem = origem;
            this.destino = destino;
            this.peso = peso;
        }
    }
    
    // Classe para o nó do heap (cada nó representará um vértice)
    static class No{
        int vertice;     // Valor que identifica o vértice, usado como índice
        int distancia;   // Distância em relação ao vértice de origem
        int antecessor;  // Armazena o vértice que o antecede no caminho mínimo
    }
    
    // Classe do grafo
    static class Grafo {
        int verticesQt;  // Número de vertices
        LinkedList<Aresta>[] listaAdj;  // Lista de adjacências (arestas) para cada vértice
        String[] rotulos;
        
        // Construtor do grafo
        Grafo(int verticesQt) {
            // Recebe a quantidade de vertices
            this.verticesQt = verticesQt;
            
            // Cria um vetor de listas de adjacências usando o número de vértices
            listaAdj = new LinkedList[verticesQt];
            rotulos = new String[verticesQt];
            
            // Inicializa uma lista de adjacências para cada vértice
            for (int i = 0; i < verticesQt; i++) {
                listaAdj[i] = new LinkedList<>();
            }
        }
        
        // Método para adicionar uma aresta à lista de adjacência dos seus 2 vértices
        // CUIDADO: não tentar adicionar uma aresta com vértices "fora" do limite do grafo
        // Exemplo: grafo com 5 vértices (índices 0-4), mas aresta a ser adicionada tem origem ou destino > 4
        public void adicionarAresta(int origem, int destino, int peso) {
            Aresta aresta = new Aresta(origem, destino, peso);
            
            // Adiciona a aresta na lista do vértice de origem
            listaAdj[origem].addFirst(aresta);
            
            // Uma aresta de sentido contrário é adicionada na lista do vértice de destino
            // Isto é uma adaptação para grafos não direcionados
            aresta = new Aresta(destino, origem, peso);
            listaAdj[destino].addFirst(aresta);
        }
        
        // Método para adicionar os rótulos de cada vértice do grafo
        public void adicionarRotulos(Scanner scanner) {
            for (int i = 0; i < verticesQt; i++) {
                rotulos[i] = scanner.nextLine();
            }
        }
        
        // Algoritmo de Dijkstra, que calcula as distâncias de cada vértice em relação à origem
        public void algoritmoDijkstra(int verticeOrigem) {
            int INFINITO = Integer.MAX_VALUE;  // Variável que simula valor infinito
            boolean[] visitados = new boolean[verticesQt];  // Armazena se um vértice já foi visitado
            
            // Cria os nós do heap em um vetor
            No[] vertices = new No[verticesQt];
            
            // Inicializa a distância de todos os vértices com infinito
            for (int i = 0; i < verticesQt; i++) {
                vertices[i] = new No();
                vertices[i].vertice = i;
                vertices[i].distancia = INFINITO;
                vertices[i].antecessor = -1;  // -1 representará que não existe antecessor
            }
            
            // Inicializa a distância do vértice de origem com 0
            vertices[verticeOrigem].distancia = 0;
            
            // Cria o heap
            MinHeap heap = new MinHeap(verticesQt);
            
            // Adiciona todos os nós (vértices) ao Heap
            for (int i = 0; i < verticesQt; i++) {
                heap.inserir(vertices[i]);
            }
            
            // Enquanto o heap não estiver vazio
            while(!heap.estaVazio()){
                // Extrair o próximo vértice a ser visitado
                No noExtraido = heap.extrairMin();
                
                // Armazena o índice do vértice extraído (em visita)
                int verticeEmVisita = noExtraido.vertice;
                
                // Já marca o vértice como visitado no vetor de visitados
                visitados[verticeEmVisita] = true;
                
                // Itera por todos os vértices adjacentes do vértice extraído
                LinkedList<Aresta> lista = listaAdj[verticeEmVisita];
                for (int i = 0; i < lista.size(); i++) {
                    Aresta aresta = lista.get(i);
                    
                    int destino = aresta.destino;  // Armazena o índice do vértice adjacente
                    
                    if(visitados[destino]==false ) {  // Verifica se esse vértice já foi visitado
                        // Se falso
                        int distanciaNova = vertices[verticeEmVisita].distancia + aresta.peso;
                        int distanciaAtual = vertices[destino].distancia;
                        
                        // Verifica se sua distância precisa ser atualizada (relaxamento)
                        if(distanciaNova < distanciaAtual){
                            // Relaxa a distância
                            relaxar(heap, distanciaNova, destino);
                            
                            // Inclui o vértice em visita como seu antecessor
                            vertices[destino].antecessor = verticeEmVisita;
                        }
                    }
                }
            }
            
            // Imprime menores distâncias e caminhos curtos
            imprimirDijkstra(vertices, verticeOrigem);
        }
        
        // Método para o relaxamento da distância do vértice e atualização de sua posição no heap
        public void relaxar(MinHeap heap, int distanciaNova, int vertice){
            // Armazena o índice do vértice cuja distância precisa ser atualizada
            int indice = heap.indices[vertice];
            
            // Usa esse índice para obter o nó do heap e atualiza seu valor
            No no = heap.heap[indice];
            no.distancia = distanciaNova;
            heap.subir(indice);  // Reposiciona esse vértice no heap
        }
        
        public void imprimirRotulos() {
            System.out.println("+---------- VÉRTICES ----------+");
            for (int i = 0; i < verticesQt; i++) {
                System.out.println("| " + i + " - " +rotulos[i]);
            }
            System.out.println("+------------------------------+");
        }
        
        // Métoto para imprimir as menores distâncias e caminhos em relação ao vértice de origem
        public void imprimirDijkstra(No[] resultados, int verticeOrigem){
            System.out.println("Resultados (Algoritmo de Dijkstra com uso de lista de adjacências + MinHeap):");
            System.out.println("Origem: vértice " + verticeOrigem + " (" + rotulos[verticeOrigem] + ")");
            
            for (int i = 0; i < verticesQt; i++) {
                // Caminhos mais curtos serão armazenados em uma pilha antes da impressão
                Stack<Integer> caminhoCurto = new Stack<>();
                
                caminhoCurto.push(i);
                for (int j = i; resultados[j].antecessor != -1; j = resultados[j].antecessor) {
                    caminhoCurto.push(resultados[j].antecessor);
                }
                
                System.out.print("Distância mínima para o vértice " + i + " (" + rotulos[i] + "): " + resultados[i].distancia + ". ");
                if(i == verticeOrigem) {
                    System.out.println("Você já está aqui!");
                    continue;
                }
                System.out.print("Caminho mais curto: " + caminhoCurto.pop());
                while(!caminhoCurto.empty()) {
                    System.out.print(" > " + caminhoCurto.pop());
                }
                System.out.print("\n");
            }
        }
    }
    
    // Classe do Heap binário, que ajudará a definir o próximo vértice a ser visitado
    // Note que se trata de um Min Heap (valores menores na raiz e extraídos primeiro)
    static class MinHeap{
        int capacidade; // Capacidade máxima do heap, recebida pelo construtor
        int tamanhoAtual;   // Monitora a quantidade atual de elementos no heap
        No[] heap;        // Vetor que representa o heap em si
        int[] indices;  // Vetor de índices, mapeia os índices dos vértices do grafo com os índices do heap

        // Construtor do MinHeap
        public MinHeap(int capacidade) {
            this.capacidade = capacidade;
            heap = new No[capacidade + 1];
            indices = new int[capacidade];
            heap[0] = new No();
            heap[0].distancia = Integer.MIN_VALUE;
            heap[0].vertice = -1;
            tamanhoAtual = 0;
        }
        /*
        public void mostrar() {
            for (int i = 0; i <= tamanhoAtual; i++) {
                System.out.println("Vértice " + heap[i].vertice + ", distância: " + heap[i].distancia);
            }
            System.out.println("________________________");
        }*/
        
        // Método para inserir um nó no heap
        public void inserir(No no) {
            tamanhoAtual++;
            int indice = tamanhoAtual;
            heap[indice] = no;
            indices[no.vertice] = indice;
            subir(indice);  // Posicionar corretamente o nó inserido no heap
        }
                
        // Método para extrair o nó de menor valor (menor distância)
        public No extrairMin() {
            No min = heap[1];
            No ultimoNo = heap[tamanhoAtual];
            
            // Atualiza o vetor de índices and move the last node to the top
            indices[ultimoNo.vertice] = 1;
            heap[1] = ultimoNo;
            heap[tamanhoAtual] = null;
            descer(1);
            tamanhoAtual--;
            return min;
        }
        
        // Método para subida de um nó com base na sua distância (não usa recursão)
        public void subir(int pos) {
            int indiceAtual = pos;  // Armazena o índice do nó recebido como argumento (filho)
            int indicePai = pos/2;  // Calcula o índice do nó pai
            
            // Enquanto a distância do nó pai for maior e o índice do nó atual > 0
            while (indiceAtual > 0 && heap[indicePai].distancia > heap[indiceAtual].distancia) {
                No noAtual = heap[indiceAtual];
                No noPai = heap[indicePai];
                
                // Atualiza o vetor de índices do heap
                // e troca as posições dos nós
                indices[noAtual.vertice] = indicePai;
                indices[noPai.vertice] = indiceAtual;
                trocar(indiceAtual, indicePai);
                indiceAtual = indicePai;
                indicePai = indicePai/2;
            }
        }
        
        // Método para descida de um nó com base na sua distância
        public void descer(int k) {
            int menor = k;  // Presume incialmente o nó do índice k como menor
            int indiceFilhoEsq = 2*k;      // Obtém os índices dos 2 filhos de k
            int indiceFilhoDir = 2*k + 1;  // para verificar adiante qual dos 3 é realmente o menor
            
            if (indiceFilhoEsq < obterTamanho() && heap[menor].distancia > heap[indiceFilhoEsq].distancia) {
                menor = indiceFilhoEsq;
            }
            if (indiceFilhoDir < obterTamanho() && heap[menor].distancia > heap[indiceFilhoDir].distancia) {
                menor = indiceFilhoDir;
            }
            if (menor != k) {  // Se k não era o menor, será necessário fazer uma troca
                No menorNo = heap[menor];
                No kNo = heap[k];
                
                // Atualiza o vetor de índices do heap
                // e troca as posições dos nós
                indices[menorNo.vertice] = k;
                indices[kNo.vertice] = menor;
                trocar(k, menor);
                descer(menor);  // Recursão
            }
        }
        
        // Método auxiliar para troca um nó com outro
        public void trocar(int a, int b) {
            No temp = heap[a];
            heap[a] = heap[b];
            heap[b] = temp;
        }
        
        // Método auxiliar para verificar se o heap está vazio
        public boolean estaVazio() {
            return tamanhoAtual == 0;
        }
        
        // Método auxiliar para obter o tamanho atual do heap
        public int obterTamanho(){
            return tamanhoAtual;
        }
    }
    
    // Main
    public static void main(String[] args) {
        String rotulosUERR = "Biblioteca\n"
                + "Coordenações\n"
                + "Laboratórios\n"
                + "Blocos de Salas A\n"
                + "Registro Acadêmico\n"
                + "Entrada 2\n"
                + "Cantina\n"
                + "Laboratório de Informática\n"
                + "Almoxarifado\n"
                + "CPCV\n"
                + "Reitoria\n"
                + "Auditório\n"
                + "Estacionamento\n"
                + "Entrada 1\n"
                + "Blocos de Salas B\n";
        Scanner rotulos = new Scanner(rotulosUERR);
        Scanner opcao = new Scanner(System.in);
        int vertices = 15;  // Já inicializado com a quantidade de vértices do grafo da UERR
        int origem;  // A ser especificado pelo usuário
        
        Grafo grafo = new Grafo(vertices);  // Cria o grafo
        
        // Adiciona as arestas do grafo representando as dependências da UERR
        grafo.adicionarAresta(0, 1, 25);
        grafo.adicionarAresta(0, 2, 34);
        grafo.adicionarAresta(1, 3, 30);
        grafo.adicionarAresta(1, 6, 45);
        grafo.adicionarAresta(2, 3, 45);
        grafo.adicionarAresta(2, 4, 25);
        grafo.adicionarAresta(3, 4, 28);
        grafo.adicionarAresta(3, 7, 30);
        grafo.adicionarAresta(4, 5, 34);
        grafo.adicionarAresta(6, 7, 22);
        grafo.adicionarAresta(7, 8, 12);
        grafo.adicionarAresta(7, 10, 110);
        grafo.adicionarAresta(7, 13, 86);
        grafo.adicionarAresta(7, 14, 56);
        grafo.adicionarAresta(8, 9, 17);
        grafo.adicionarAresta(10, 11, 36);
        grafo.adicionarAresta(10, 14, 50);
        grafo.adicionarAresta(11, 12, 46);
        grafo.adicionarAresta(11, 14, 42);
        grafo.adicionarAresta(12, 13, 32);
        grafo.adicionarAresta(12, 14, 25);
        grafo.adicionarAresta(13, 14, 38);
        
        grafo.adicionarRotulos(rotulos);  // Adiciona o rótulo de cada vértice
        grafo.imprimirRotulos();          // e os imprime em um menu
        
        System.out.print("Digite o número de seu local de origem: ");
        origem = opcao.nextInt();
        
        grafo.algoritmoDijkstra(origem);
    }
}