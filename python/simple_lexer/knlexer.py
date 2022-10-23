"""Simple lexical analyzer implementation by Lekiyoshi

Made as practice for my compiler construction classes.
Loosely based on Python language keywords and operators.
It is directly based on simulation of a finite state machine
and does not make use of regular expressions to recognize patterns."""

from tabulate import tabulate

token_dict = {  # lexeme: token as in value: type
    'and': 'AND',
    'assert': 'ASSERT',
    'break': 'BREAK',
    'class': 'CLASS',
    'continue': 'CONTINUE',
    'def': 'DEF',
    'do': 'DO',
    'else': 'ELSE',
    'except': 'EXCEPT',
    'false': 'FALSE',
    'finally': 'FINALLY',
    'for': 'FOR',
    'if': 'IF',
    'not': 'NOT',
    'null': 'NULL',
    'or': 'OR',
    'pass': 'PASS',
    'raise': 'RAISE',
    'return': 'RETURN',
    'true': 'TRUE',
    'try': 'TRY',
    'while': 'WHILE',
    'yield': 'YIELD',
    '+': 'PLUS',
    '-': 'MINUS',
    '*': 'STAR',
    '/': 'SLASH',
    '%': 'PERCENT',
    '=': 'EQUAL',
    '+=': 'PLUS_EQUAL',
    '-=': 'MINUS_EQUAL',
    '*=': 'STAR_EQUAL',
    '/=': 'SLASH_EQUAL',
    '%=': 'PERCENT_EQUAL',
    '==': 'EQ_EQUAL',
    '!=': 'NOT_EQUAL',
    '<': 'LESS',
    '>': 'GREATER',
    '<=': 'LESS_EQUAL',
    '>=': 'GREATER_EQUAL',
    '&': 'AMPERSAND',
    '|': 'V_BAR',
    '^': 'CARET',
    '~': 'TILDE',
    '<<': 'L_SHIFT',
    '>>': 'R_SHIFT',
    '(': 'L_PAR',
    ')': 'R_PAR',
    '[': 'L_BRACKET',
    ']': 'R_BRACKET',
    '{': 'L_BRACE',
    '}': 'R_BRACE',
    ',': 'COMMA',
    '.': 'DOT',
    ';': 'SEMICOLON',
    ':': 'COLON'
}
state_dict = {  # First lexeme char: Initial state
    '+': 41, '-': 41,
    '*': 41, '/': 41,
    '%': 41,
    '=': 41, '!': 42,
    '<': 43, '>': 44,
    '&': 45, '|': 45,
    '^': 45, '~': 45,
    '(': 51, ')': 51,
    '[': 51, ']': 51,
    '{': 51, '}': 51,
    ',': 51, '.': 52,
    ';': 51, ':': 51,
}

digits = "0123456789"
word_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"


def lexer(filename):
    with open(filename, mode='rt', buffering=4096, encoding='utf-8') as f:

        symbol_table = []  # Currently only stores (lexeme, token, row) tuples
        c = None  # Stores current scanned character
        lexeme = ""  # Tracks current lexeme being scanned
        row = 1  # Tracks row number, begins at 1 and increases for each '\n' scanned

        state = 0  # Shared variable that stores current state for the FSM of each group
        # 0: Begin, 1_: Identifier, 2_: Numeric, 3_: String, 4_: Operator, 5_: Delimiter, 6_: Ignore, 7_: Invalid

        def create_token(token_name):
            nonlocal row
            nonlocal lexeme
            if lexeme:
                return lexeme, token_name, row

        def lexeme_begin():
            nonlocal c
            nonlocal lexeme
            nonlocal row
            nonlocal state

            if c in " \r\t":  # Whitespace chars are not inserted in current lexeme
                state = 61
            elif c == '\n':
                state = 62
            elif c == '#':  # '#' begins a comment, which is also ignored
                state = 63
            elif c in state_dict:
                state = state_dict[c]
                lexeme = c
            elif c == "'":  # Quotation marks are not inserted in current lexeme
                state = 31
                lexeme = ""
            elif c == '"':
                state = 32
                lexeme = ""
            elif c in digits:
                state = 21
                lexeme = c
            elif c in word_chars:
                state = 11
                lexeme = c
            else:
                state = 71
                lexeme = c

        while c != '':  # Empty string is used to signal end of file
            c = f.read(1)  # Scanning by each character

            # Note: There is no backtracking implemented.
            #       Backtracking would have been needed for only one character each time.
            #       Instead of backtracking that single character to find the right lexeme,
            #       avoid adding it to the current lexeme and generate the token.
            #       Only then add that character to the beginning of a new lexeme, using 'lexeme_begin()'.

            match state:
                case 0:
                    lexeme_begin()

                case 11:
                    if c in word_chars or c in digits:
                        lexeme += c
                    else:
                        if lexeme in token_dict:
                            symbol_table.append(create_token(token_dict[lexeme]))
                        else:
                            symbol_table.append(create_token("IDENTIFIER"))
                        lexeme_begin()

                case 21:
                    if c in digits:
                        lexeme += c
                    elif c == '.':
                        state = 22
                        lexeme += c
                    else:
                        symbol_table.append(create_token("INTEGER"))
                        lexeme_begin()

                case 22:
                    if c in digits:
                        state = 23
                        lexeme += c
                    else:
                        symbol_table.append(create_token("FLOAT"))
                        lexeme_begin()

                case 23:
                    if c in digits:
                        lexeme += c
                    else:
                        symbol_table.append(create_token("FLOAT"))
                        lexeme_begin()

                case 31:  # String began with '
                    if c == "'":
                        state = 33
                    else:
                        lexeme += c

                case 32:  # String began with "
                    if c == '"':
                        state = 33
                    else:
                        lexeme += c

                case 33:  # String has finished
                    symbol_table.append(create_token("STRING"))
                    lexeme_begin()

                case 41:  # Began with: '+', '-', '*', '/', '%', '='
                    if c == '=':
                        state = 45
                        lexeme += c
                    else:
                        symbol_table.append(create_token(token_dict[lexeme]))
                        lexeme_begin()

                case 42:  # Began with: '!'
                    if c == '=':
                        state = 45
                        lexeme += c
                    else:
                        symbol_table.append(create_token("INVALID_CHAR"))
                        lexeme_begin()

                case 43:  # Began with: '<'
                    if c == '=' or c == '<':
                        state = 45
                        lexeme += c
                    else:
                        symbol_table.append(create_token(token_dict[lexeme]))
                        lexeme_begin()

                case 44:  # Began with: '>'
                    if c == '=' or c == '>':
                        state = 45
                        lexeme += c
                    else:
                        symbol_table.append(create_token(token_dict[lexeme]))
                        lexeme_begin()

                case 45:  # '&', '|', '^', '~', '+=', '-=', '*=', '/=', '%=', '==', '!=', '<=', '>=', '<<', '>>'
                    symbol_table.append(create_token(token_dict[lexeme]))
                    lexeme_begin()

                # This state could have been merged with the one above,
                # but kept separe because it starts a different group of tokens
                case 51:  # '(', ')', [', ']', '{', '}', ',', ';', ':'
                    symbol_table.append(create_token(token_dict[lexeme]))
                    lexeme_begin()

                case 52:  # '.'
                    if c in digits:
                        state = 23  # A float literal can also begin with '.'
                        lexeme += c
                    else:
                        symbol_table.append(create_token(token_dict[lexeme]))
                        lexeme_begin()

                case 61:  # Whitespace ' ', '\r', '\t'
                    lexeme_begin()

                case 62:  # Whitespace '\n'
                    row += 1  # Increase row count if '\n' was read
                    lexeme_begin()

                case 63:  # Scanning a comment
                    if c == '\n':  # A comment ends with a new line
                        lexeme_begin()

                case 71:  # Invalid character
                    symbol_table.append(create_token("INVALID_CHAR"))
                    lexeme_begin()

            # print(c)
            # print(state)
            # print(lexeme)

    return symbol_table


if __name__ == '__main__':
    filename = "exemplo5.txt"

    symbol_table = lexer(filename)
    print("Token sequence:")
    print(tabulate(symbol_table, headers=["Lexeme", "Token", "Row"]))
