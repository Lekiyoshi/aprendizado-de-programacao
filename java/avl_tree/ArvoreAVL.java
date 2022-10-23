/**
 * Implementação de Árvore AVL
 */

package edii_bst;

import java.util.Scanner;

// Árvore AVL
// É uma Árvore Binária de Busca com mecanismo de auto balanceamento.

// As alturas de cada subárvore de um nó não diferem em mais que 1.
// Para manter essa propriedade após inserir ou deletar nós, são realizados operações de "rotação".

// A diferença das alturas das duas subárvores é denominada 'fator de balanço'.
// Seu valor abaixo de -1 ou acima de 1 sinaliza necessidade de fazer até duas rotações.

// Uma árvore auto balanceada mantém uma altura mínimizada ou próxima da mínima.
// Isso favorece operações de acesso e leitura com complexidade média de O(log n).
// Operações de inserir e deletar também possuem complexidade média de O(log n).

// CASO ESQUERDA-ESQUERDA
// T1, T2, T3 e T4 são subárvores.
//         z                                      y
//        / \                                   /   \
//       y   T4   Rotacionar Direita (z)       x     z
//      / \         - - - - - - - - ->       /  \   /  \
//     x   T3                               T1  T2 T3  T4
//    / \
//  T1   T2

// CASO ESQUERDA-DIREITA
//       z                               z                               x
//      / \                            /   \                           /   \
//     y   T4  Rotacionar Esq. (y)    x    T4  Rotacionar Dir. (z)    y     z
//    / \      - - - - - - - - ->    / \       - - - - - - - - ->   /  \   /  \
//  T1   x                          y   T3                         T1  T2 T3  T4
//      / \                        / \
//    T2   T3                    T1   T2

// CASO DIREITA-DIREITA
//     z                                          y
//    / \                                       /   \
//  T1   y        Rotacionar Esquerda (z)      z     x
//      / \         - - - - - - - - ->       /  \   /  \
//    T2   x                                T1  T2 T3  T4
//        / \
//      T3   T4

// CASO DIREITA-ESQUERDA
//     z                               z                                 x
//    / \                             / \                              /   \
//  T1   y     Rotacionar Dir. (y)  T1   x     Rotacionar Esq.(z)     z     y
//      / \    - - - - - - - - ->      /  \    - - - - - - - - ->   /  \   /  \
//     x   T4                         T2   y                       T1  T2 T3  T4
//    / \                                /  \
//  T2   T3                             T3   T4

public class ArvoreAVL {
    No raiz = null;
    int registro = 0;
    
    static class No {
        int chave;
        int altura;
        String nome;
        double preco;
        No esq;
        No dir;
        
        No(int chave, String nome, double preco) {
            this.chave = chave;
            this.altura = 1;
            this.nome = nome;
            this.preco = preco;
            this.esq = this.dir = null;
        }
    }
    
    // Método para obter altura de uma árvore
    int obterAltura(No no) {
        if (no == null){
            return 0;
        }
        return no.altura;
    }
    
    // Método auxiliar para obter o maior entre 2 valores
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    // Método para rotacionar para a direita a subárvore à esquerda de 'y'
    No rotacionarDir(No y) {
        No x = y.esq;
        No z = x.dir;
        
        //     y
        //    / \
        //   x   
        //  / \
        //     z
        
        // Faz a rotação
        x.dir = y;
        y.esq = z;
        
        //   x
        //  / \
        //     y
        //    / \
        //   z
        
        // Atualiza as alturas
        y.altura = max(obterAltura(y.esq), obterAltura(y.dir)) + 1;
        x.altura = max(obterAltura(x.esq), obterAltura(x.dir)) + 1;
        
        // 'x' terá substituído 'y' como raiz
        return x;
    }
    
    // Método para rotacionar para a esquerda a subárvore à direita de 'x'
    No rotacionarEsq(No x) {
        No y = x.dir;
        No z = y.esq;
        
        //   x
        //  / \
        //     y
        //    / \
        //   z
        
        // Faz a rotação
        y.esq = x;
        x.dir = z;
        
        //     y
        //    / \
        //   x   
        //  / \
        //     z
        
        // Atualiza as alturas
        x.altura = max(obterAltura(x.esq), obterAltura(x.dir)) + 1;
        y.altura = max(obterAltura(y.esq), obterAltura(y.dir)) + 1;
        
        // 'y' terá substituído 'x' como raiz
        return y;
    }
    
    // Método para obter o fator de balanço, que é a diferença de altura das duas subárvores
    int obterBalanco(No no) {
        if (no == null){
            return 0;
        }
        // Valor negativo: subárvore direita tem maior altura
        // Valor positivo: subárvore esquerda tem maior altura
        return obterAltura(no.esq) - obterAltura(no.dir);
    }
    
    // Método para inserir
    No inserir(No no, int chave, String nome, double preco) {
        // Primeiro insere como em uma árvore binária de busca padrão
        
        if (no == null) {  // Insere assim que encontramos uma posição vazia
            return (new No(chave, nome, preco));
        }
        
        if (chave < no.chave) {  // Vai para a esquerda caso a chave seja menor
            no.esq = inserir(no.esq, chave, nome, preco);
        }
        else if (chave > no.chave) {  // Para a direita caso seja maior
            no.dir = inserir(no.dir, chave, nome, preco);
        }
        else {  // Interrompe caso a chave seja repetida
            return no;
        }
        
        // Atualiza a altura do nó atual
        no.altura = 1 + max(obterAltura(no.esq), obterAltura(no.dir));
        
        // Obtém o fator de balanço do nó atual
        int balanco = obterBalanco(no);
        
        // Se houver desbalanço, verificar qual dos 4 casos possíveis:
        
        // Caso esquerda-esquerda
        if (balanco > 1 && chave < no.esq.chave) {
            return rotacionarDir(no);
        }
        
        // Caso direita-direita
        if (balanco < -1 && chave > no.dir.chave) {
            return rotacionarEsq(no);
        }
        
        // Caso esquerda-direita
        if (balanco > 1 && chave > no.esq.chave) {
            no.esq = rotacionarEsq(no.esq);
            return rotacionarDir(no);
        }
        
        // Caso direita-esquerda
        if (balanco < -1 && chave < no.dir.chave) {
            no.dir = rotacionarDir(no.dir);
            return rotacionarEsq(no);
        }
        
        // Caso sem desbalanço
        return no;
    }
    
    // Método auxiliar para obter o nó com a menor chave da árvore
    No menorChave(No no) {
        No temp = no;
        
        // Será aquele que estiver mais à esquerda
        while (temp.esq != null) {
            temp = temp.esq;
        }
        return temp;
    }
    
    // Método para deletar
    No deletar(No no, int chave) {
        // Primeiro deleta assim como em uma árvore binária de busca padrão
        
        // Caso o primeiro nó seja nulo, a árvore já está vazia!
        if (no == null) {
            return no;
        }
        
        if (chave < no.chave) {  // Vai para a esquerda caso a chave seja menor
            no.esq = deletar(no.esq, chave);
        }
        else if (chave > no.chave) {  // Para a direita caso seja maior
            no.dir = deletar(no.dir, chave);
        }
        else {  // Se as chaves são iguais, encontramos o nó a ser deletado
            // Será preciso verificar se o nó a ser deletado tem filhos
            if ((no.esq == null) || (no.dir == null)) {  // Caso com 0 ou 1 filho
                No temp = null;
                if (temp == no.esq) {
                    temp = no.dir;
                } else {
                    temp = no.esq;
                }
                // Depois dessa etapa, 'temp' estará apontando para o filho único, se houver um
                
                if (temp == null) {  // Caso sem filhos
                    no = null;
                } else {  // Caso com apenas um filho
                    no = temp;  // Copia de 'temp' para o nó atual
                }
            }
            else {  // Caso com dois filhos
                // Obtém o sucessor inorder da subárvore direita
                No temp = menorChave(no.dir);
                
                // Copia os dados do sucessor inorder para o nó atual
                no.chave = temp.chave;
                no.altura = temp.altura;
                no.nome = temp.nome;
                no.preco = temp.preco;
                
                // Deleta o sucessor inorder, que mudou de posição
                no.dir = deletar(no.dir, temp.chave);
            }
        }
 
        // Se havia apenas um nó na árvore, não há mais nada a ser feito
        if (no == null) {
            return no;
        }
        
        // Caso contrário
        // Atualiza a altura do nó atual
        no.altura = max(obterAltura(no.esq), obterAltura(no.dir)) + 1;
        
        // Obtém o fator de balanço para o nó atual
        int balanco = obterBalanco(no);
        
        // Se houver desbalanço, verificar qual dos 4 casos possíveis:
        
        // Caso esquerda-esquerda
        if (balanco > 1 && obterBalanco(no.esq) >= 0){
            return rotacionarDir(no);
        }
        
        // Caso esquerda-direita
        if (balanco > 1 && obterBalanco(no.esq) < 0) {
            no.esq = rotacionarEsq(no.esq);
            return rotacionarDir(no);
        }
        
        // Caso direita-direita
        if (balanco < -1 && obterBalanco(no.dir) <= 0) {
            return rotacionarEsq(no);
        }
        
        // Caso direita-esquerda
        if (balanco < -1 && obterBalanco(no.dir) > 0) {
            no.dir = rotacionarDir(no.dir);
            return rotacionarEsq(no);
        }
        
        // Caso sem desbalanço
        return no;
    }
    
    void alterar(No no, String nome, double preco) {
        no.nome = nome;
        no.preco = preco;
        System.out.println("Produto alterado com sucesso!");
    }
    
    void imprimirNo(No no) {
        System.out.println("Código: " + no.chave
                + " - Produto: " + no.nome
                + " - Preço: " + no.preco);
    }
    
    No buscar(No no, int chave) {
        if (no == null) {
            System.out.println("Produto não encontrado!");
            return null;
        }
        
        No temp;
        
        if (chave < no.chave) {
            temp = buscar(no.esq, chave);
        } else if (chave > no.chave) {
            temp = buscar(no.dir, chave);
        } else {
            System.out.println("Produto encontrado: ");
            imprimirNo(no);
            temp = no;
        }
        
        return temp;
    }
    
    void imprimirPreOrder(No no) {
        if (no != null) {
            imprimirNo(no);
            imprimirPreOrder(no.esq);
            imprimirPreOrder(no.dir);
        }
    }
    
    void imprimirInOrder(No no) {
        if (no != null) {
            imprimirInOrder(no.esq);
            imprimirNo(no);
            imprimirInOrder(no.dir);
        }
    }
    
    void imprimirPostOrder(No no) {
        if (no != null) {
            imprimirPostOrder(no.esq);
            imprimirPostOrder(no.dir);
            imprimirNo(no);
        }
    }
    
    // Método para imprimir um nível específico de uma árvore binária
    void imprimirNivel(No no, int r, int h) {
        // Calcula o recuo que cada elemento no nível terá, baseado na altura da árvore
        // Isso é necessário para manter os elementos nas posições corretas ao usar 'mostrarArvore'
        int recuo = 6 * (int)Math.pow(2, h - r - 1) - 3;

        // Caso base
        if (no == null) {
            // Imprime os espaços vazios do nível, baseado em quantos níveis faltam para a função
            // chegar na base da árvore
            int niveis_faltantes = (int)Math.pow(2, r - 1);
            
            for (int i = 0; i < niveis_faltantes; i++) {
                for (int j = 0; j < recuo; j++) {
                    System.out.print("_");
                }
                
                System.out.print("_    _");  // Espaço vazio.
                
                for (int k = 0; k < recuo; k++) {
                    System.out.print("_");
                }
            }
            
            return;
        }

        // Caso 'r' seja 1, já estamos no nível a ser impresso
        if (r == 1) {
            for (int i = 0; i < recuo; i++) {
                System.out.print("_");
            }
            
            System.out.print("_(");
            System.out.format("%02d", no.chave);
            System.out.print(")_");
            
            for (int i = 0; i < recuo; i++) {
                System.out.print("_");
            }
        }
        // Caso 'r' seja maior que 1, ainda não estamos no nível desejado e a função é chamada
        // recursivamente para cada subárvore
        else if (r > 1) {
            imprimirNivel(no.esq, r - 1, h - 1);
            imprimirNivel(no.dir, r - 1, h - 1);
        }
    }
    
    // Método para imprimir todos os níveis da árvore binária
    void mostrarArvore(No no) {
        int h = obterAltura(no);  // Obtém a altura da árvore para passar como parâmetro
        
        for (int i = 1; i <= h; i++) {  // Iteração pela quantidade de níveis, determinada por 'h'
            imprimirNivel(no, i, h);
            System.out.println("\n");
        }
    }
    
    // Main
    public static void main(String[] args) {
        ArvoreAVL produtos = new ArvoreAVL();
        Scanner texto = new Scanner(System.in);
        int opcaoMenu, codigo;
        String nome;
        double preco;
        
        produtos.raiz = produtos.inserir(produtos.raiz, (produtos.registro)++, "Banana", 2.0);
        produtos.raiz = produtos.inserir(produtos.raiz, (produtos.registro)++, "Maca", 4.5);
        produtos.raiz = produtos.inserir(produtos.raiz, (produtos.registro)++, "Laranja", 3.0);
        produtos.raiz = produtos.inserir(produtos.raiz, (produtos.registro)++, "Abacaxi", 5.0);
        produtos.raiz = produtos.inserir(produtos.raiz, (produtos.registro)++, "Uva", 8.0);
        produtos.raiz = produtos.inserir(produtos.raiz, (produtos.registro)++, "Manga", 3.5);
        produtos.raiz = produtos.inserir(produtos.raiz, (produtos.registro)++, "Pera", 5.5);
        
        do {
            System.out.println("+------------ MENU ------------+");
            System.out.println("| 1. Inserir produto           |");
            System.out.println("| 2. Excluir produto           |");
            System.out.println("| 3. Alterar produto           |");
            System.out.println("| 4. Buscar produto            |");
            System.out.println("| 5. Imprimir PreOrder         |");
            System.out.println("| 6. Imprimir InOrder          |");
            System.out.println("| 7. Imprimir PostOrder        |");
            System.out.println("| 8. Mostrar Árvore            |");
            System.out.println("| 9. Sair                      |");
            System.out.println("+------------------------------+");
            
            System.out.print("Selecione uma opção: ");
            
            opcaoMenu = texto.nextInt();
            texto.nextLine();  // Evitar que nextLine() obtenha '\n' logo após o número da opção
            
            outer:
            switch(opcaoMenu) {
                case 1:
                    System.out.print("Informe o nome do produto a ser inserido: ");
                    nome = texto.nextLine();
                    System.out.print("Informe o preço do produto: ");
                    preco = texto.nextDouble();
                    texto.nextLine();
                    
                    produtos.raiz = produtos.inserir(
                            produtos.raiz, (produtos.registro)++, nome, preco);
                    System.out.println();
                    break;
                    
                case 2:
                    System.out.print("Informe o código de registro do produto a ser deletado: ");
                    codigo = texto.nextInt();
                    texto.nextLine();
                    
                    produtos.raiz = produtos.deletar(produtos.raiz, codigo);
                    System.out.println();
                    break;
                    
                case 3:
                    System.out.print("Informe o código de registro do produto para alteração: ");
                    codigo = texto.nextInt();
                    texto.nextLine();
                    
                    No busca = produtos.buscar(produtos.raiz, codigo);
                    if (busca != null) {
                        System.out.print("Informe o novo nome: ");
                        nome = texto.nextLine();
                        System.out.print("Informe o novo preço: ");
                        preco = texto.nextDouble();
                        texto.nextLine();
                        
                        produtos.alterar(busca, nome, preco);
                        produtos.imprimirNo(busca);
                        busca = null;
                    }
                    
                    System.out.println();
                    break;
                    
                case 4:
                    System.out.print("Informe o código de registro do produto para busca: ");
                    codigo = texto.nextInt();
                    texto.nextLine();
                    
                    produtos.buscar(produtos.raiz, codigo);
                    System.out.println();
                    break;
                    
                case 5:
                    produtos.imprimirPreOrder(produtos.raiz);
                    System.out.println();
                    break;
                    
                case 6:
                    produtos.imprimirInOrder(produtos.raiz);
                    System.out.println();
                    break;
                    
                case 7:
                    produtos.imprimirPostOrder(produtos.raiz);
                    System.out.println();
                    break;
                    
                case 8:
                    produtos.mostrarArvore(produtos.raiz);
                    System.out.println();
                    break;
                    
                case 9:
                    break;
                    
                default:
                    System.out.println("Opção inválida.\n");
                    break;
            }
        }
        
        while (opcaoMenu != 9);
    }
}
