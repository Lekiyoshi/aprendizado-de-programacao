from random import randint


def sorteio(n, a, b):
    sorteados = []  # cada lista começa vazia

    for i in range(n):  # 'n' define a quantidade de números gerados aleatoriamente
        sucesso = False  # para verificar se número sorteado não é repetido

        while not sucesso:
            numero = randint(a, b)  # gera um número aleatório entre 'a' e 'b' (estes também inclusos)

            for j in sorteados:
                if numero == j:
                    break
            else:
                sucesso = True

        sorteados.append(numero)

    return sorteados


for x in range(60):
    cartao = sorteio(6, 1, 60)
    print(cartao)
