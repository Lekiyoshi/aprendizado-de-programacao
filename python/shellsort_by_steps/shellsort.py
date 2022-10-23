"""
Implementação de Shell sort para a disciplina de Complexidade de Algoritmos.
Neste módulo, o Shell sort é comparado ao Insertion sort pelo
número de comparações totais entre elementos de um mesmo array randomizado.
"""

from random import randint


# A implementação simples do Shell sort
def shell_sort(array):
    n = len(array)  # Número de elementos do array
    h = n // 2  # Intervalo que será reduzido progressivamente até 0 (n/2, n/4, n/8 ... 0)

    while h > 0:
        for i in range(h, n):
            temp = array[i]  # Variável para auxiliar trocas
            j = i
            while j >= h and array[j - h] > temp:
                array[j] = array[j - h]
                j -= h
            array[j] = temp
        h //= 2


# Versão que informa os estados do array e seus sub-arrays, além da quantidade de comparações realizadas
def shell_sort_by_steps(array):
    n = len(array)  # Número de elementos do array
    h = n // 2  # Intervalo que será reduzido progressivamente até 0 (n/2, n/4, n/8 ... 0)
    comparisons = 0  # Quantidade total de comparações

    print("Início:", array)

    while h > 0:
        print("\nIntervalo (h):", h)
        print("Estado atual:")
        print_sub_array(array, sep='')

        for i in range(h, n):
            comp = 1  # Armazena quantidades de comparações realizadas
            swap = False  # Armazena se houve troca de posições
            temp = array[i]  # Variável para auxiliar trocas
            j = i

            print()
            print_sub_array(array, i, h, sep='')

            while j >= h and array[j - h] > temp:  # Pelo menos uma comparação acontece
                array[j] = array[j - h]
                j -= h
                comp += 1
                swap = True
            array[j] = temp
            comparisons += comp

            if swap:
                print_sub_array(array, i, h, sep='')

        h //= 2

    print("\nFim:", array, "\nComparações totais:", comparisons)


def print_sub_array(array: list, k=None, h=1, **kwargs):
    """
    Imprime os sub-arrays do Shell sort para melhor visualização do funcionamento do algoritmo.
    Caso se queira imprimir o array inteiro, não especificar 'k' e 'h' na chamada da função.
    Dessa maneira o intervalo 'h' será 1 e 'k' receberá o índice do último elemento da lista.

    :param array: É a lista que será ordenada pelo Shell sort.
    :param k: Indica até qual elemento mais à direita da lista deve ser impresso.
    :param h: É o intervalo recebido do algoritmo Shell sort.
    :param kwargs: Repassa os argumentos de palavra-chave para a função print().
    """
    n = len(array)
    k = k or n-1  # Usa o índice do último elemento se 'k' não foi especificado
    max_len = max(map(len, map(str, array)))  # Encontra o comprimento do número mais longo da lista
    aux_list = []

    for i in range(n):
        # Vai incluir na impressão apenas elementos à esquerda de 'k' com 'h' de intervalo
        if (k-i) % h == 0 and i <= k:
            aux_list.append("{x:{y}}".format(x=array[i], y=max_len))  # Usa 'max_len' para padronizar o espaçamento
        else:
            aux_list.append("{x:{y}}".format(x='', y=max_len))

    print("[", ", ".join(aux_list), "]", **kwargs)


def randint_array(array: list, n, min, max):
    """
    Modifica uma lista, inserindo n valores inteiros aleatórios entre min e max.
    """
    n = 1 if n < 1 else n
    max = min if max < min else max
    array.clear()  # Remove qualquer elemento que já esteja na lista
    for i in range(n):
        array.append(randint(min, max))  # Adiciona os números aleatórios


# Implementação simples de Insertion sort que informa a quantidade de comparações realizadas
def insertion_sort(array):
    n = len(array)
    comparisons = 0

    print("Início:", array)

    for i in range(n):
        temp = array[i]  # Variável para auxiliar trocas
        j = i - 1
        comp = 1

        while j >= 0 and array[j] > temp:
            array[j + 1] = array[j]
            j -= 1
            comp += 1
        array[j + 1] = temp
        comparisons += comp

    print("Fim:   ", array, "\nComparações totais:", comparisons)


if __name__ == '__main__':
    dados = []
    randint_array(dados, 15, 0, 100)
    dados2 = [x for x in dados]  # Faz uma cópia da lista para ser usada no Insertion sort

    # Comparativo do Shell sort com Insertion sort usando a mesma lista gerada
    print("-------------------------- Shell Sort --------------------------")
    shell_sort_by_steps(dados)
    print()
    print("------------------------ Insertion Sort ------------------------")
    insertion_sort(dados2)
