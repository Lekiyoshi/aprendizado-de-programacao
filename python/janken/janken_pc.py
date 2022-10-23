from random import randint


# itens = ("Pedra", "Papel", "Tesoura")

com1_pt = 0
com2_pt = 0
empates = 0

for _ in range(0, 2000):
    com1 = randint(0, 2)
    com2 = randint(0, 2)
    resultado = com1 + (com2 << 2)

    if resultado in [2, 4, 9]:
        com2_pt += 1
    elif resultado in [1, 6, 8]:
        com1_pt += 1
    else:
        empates += 1

print("""O Computador1 venceu {x} partidas.
O Computador2 venceu {y} partidas.
Houve {z} empates.""".format(x=com1_pt, y=com2_pt, z=empates))

if com1_pt > com2_pt:
    print("O Computador1 venceu mais!")
elif com2_pt > com1_pt:
    print("O Computador2 venceu mais!")
else:
    print("Os computadores empataram!")
