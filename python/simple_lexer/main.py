# Analisador léxico simples
# Não consegue identificar strings e comentários

import re
import knlexer as kn
from tabulate import tabulate


# Simulação de autômato finito para identificadores ou números
def fsm_id_num(palavra):
    estados_finais = ["INTEGER", "FLOAT", "IDENTIFIER"]
    estado_atual = "START"
    lexema = ""

    for c in palavra:
        lexema += c

        if estado_atual == "START":
            if re.search(r"\d", c):
                estado_atual = "INTEGER"
            elif re.search(r"[A-Za-z_]", c):
                estado_atual = "IDENTIFIER"
            else:
                estado_atual = "ERROR"

        elif estado_atual == "INTEGER":
            if re.search(r"\d", c):
                pass
            elif c == ".":
                estado_atual = "N2"
            else:
                estado_atual = "ERROR"

        elif estado_atual == "N2":
            if re.search(r"\d", c):
                estado_atual = "FLOAT"
            else:
                estado_atual = "ERROR"

        elif estado_atual == "FLOAT":
            if re.search(r"\d", c):
                pass
            else:
                estado_atual = "ERROR"

        elif estado_atual == "IDENTIFIER":
            if re.search(r"[0-9A-Za-z_]", c):
                pass
            else:
                estado_atual = "ERROR"

    if estado_atual in estados_finais:
        return estado_atual  # Os nomes dos estados finais já correspondem aos tokens dos lexemas
    else:
        return "ERROR"


# Gerador de tokens
def tokenizador(palavra):
    token = [palavra]

    # Primeiro verifica se a palavra já esta na lista de palavras reservadas, operadores e delimitadores
    if palavra in kn.token_dict:
        token.append(kn.token_dict[palavra])
    else:
        token.append(fsm_id_num(palavra))  # Se não estiver na lista, então é um número ou identificador

    return token


# Analisador léxico, prepara o código fonte/string para o gerador de tokens
def analizador_lexico(codigo):
    f = open(codigo, mode='rt', encoding='utf-8')
    arquivo = f.read()

    tabela_simbolos = []

    # Procedimento de substituição com regex para "desgrudar" operadores e delimitadores
    op_regex = r"(\+=|\+|-=|-|\*=|\*|/=|/|%=|%|==|=|!=|<=|>=|<<|>>|<|>|&|\||\^|~|\(|\)|\[|\]|\{|\}|,|;|:)"
    palavras = re.sub(op_regex, r" \1 ", arquivo)

    # O split abaixo usa espaços entre as palavras para separação em uma lista, por isso foi necessário o regex acima
    palavras = palavras.split()

    for w in palavras:
        tabela_simbolos.append(tokenizador(w))

    f.close()

    return tabela_simbolos


def main():
    nome_arquivo = "exemplo4.txt"

    # Primeiro analisador léxico
    tabela_simbolos = analizador_lexico(nome_arquivo)
    print("Sequência de tokens:")
    print(tabulate(tabela_simbolos, headers=["Lexema", "Token"]))

    print()

    # Analisador léxico alternativo, criado sem o uso de expressões regulares
    symbol_table = kn.lexer(nome_arquivo)
    print("Token sequence:")
    print(tabulate(symbol_table, headers=["Lexeme", "Token", "Row"]))


if __name__ == '__main__':
    main()
