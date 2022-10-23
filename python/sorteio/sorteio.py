from random import randint


def sorteio(n, a, b):  # evitar n > b, pois não pode haver repetição
    sorteados = []  # cada lista começa vazia

    for i in range(n):  # 'n' define a quantidade de números gerados aleatoriamente
        numero = randint(a, b)  # gera um número aleatório entre 'a' e 'b' (estes também inclusos)

        # o próximo loop vai comparar o número novo
        # com aqueles já adicionados na lista (representados por 'j')
        for j in sorteados:
            if numero >= j:  # se o número novo for maior ou igual que 'j'
                numero += 1  # será aumentado em 1

        sorteados.append(numero)
        sorteados.sort()  # infelizmente descobri que o algoritmo só funciona se a lista estiver ordenada
        b -= 1  # essa linha é a razão de ser adicionado o loop acima

        # exemplo: 42 foi o primeiro número a ser gerado entre 1 e 60
        # o próximo número será gerado de 1 a 59 (pq 'b' terá reduzido em 1)
        # supondo que o segundo número seja 42 de novo (ou maior), será aumentado em 1
        # evitando repetição e mantendo a geração
        # entre 1 e 60 com chances iguais para os números restantes

    return sorteados


for x in range(60):
    cartao = sorteio(6, 1, 60)
    print(cartao)
