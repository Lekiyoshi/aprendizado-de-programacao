from random import randint
from time import sleep


itens = ("Pedra", "Papel", "Tesoura")

computador = randint(0, 2)

print("""Jogadas possíveis:
[0] Pedra
[1] Papel
[2] Tesoura""")

jogador = int(input("Qual a sua jogada? "))

print("Jan")
sleep(1)
print("Ken")
sleep(1)
print("Pon")
sleep(1)

print(f"O Computador usou: {itens[computador]}")
print(f"O Jogador usou: {itens[jogador]}")
print("-="*16)

resultado = computador + (jogador << 2)

# O resultado pode ser interpretado como um valor de 4 bits
# Os dois bits mais significantes representam a jogada do jogador
# e os dois menos significantes representam a jogada do computador
# 00 = pedra
# 01 = papel
# 10 = tesoura
# O numero decimal formado pelos 4 bits pode revelar quem venceu ou se houve empate

if resultado in [2, 4, 9]:
    print("O Jogador venceu!")
elif resultado in [1, 6, 8]:
    print("O Computador venceu!")
else:
    print("Empatou!")
