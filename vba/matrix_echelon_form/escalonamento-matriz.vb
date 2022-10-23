Dim L As Integer   'Quantidade de linhas
Dim C As Integer   'Quantidade de colunas
Dim M As Double    'Essa variável é equivalente ao P1/P2 do código anterior
Dim Oi As Integer  'Deslocamento de linhas
Dim Oj As Integer  'Deslocamento de colunas
Dim X As String    'Letra da coluna mais à esquerda
Dim Y As String    'Letra da coluna mais à direita
Dim Q As Variant   'Auxiliador na cópia de intervalos

'As variáveis 'I' e 'J' serão usadas para linhas e colunas nos loops For em vez de
'usar 'L' e 'C', preservando seus valores originais caso sejam necessários novamente.

'As variáveis 'Oi' e 'Oj' definem a partir de qual célula a matriz será gerada
'e seus valores são calculados a partir do endereço inserido como topo esquerdo.

Sub Escalonar()
    'L = InputBox("Informe o número de linhas", "Informe as dimensões da matriz")
    'C = InputBox("Informe o número de colunas", "Informe as dimensões da matriz")
    
    'Desde que as primeiras 3 linhas da planilha não tenham sido editadas,
    'as seguintes variáveis vão obter os valores corretos.
    Oi = Range(Cells(2, 21)).Row - 1
    Oj = Range(Cells(2, 21)).Column - 1
    L = Cells(2, 12)
    C = Cells(2, 16)
    X = Split(Cells(1, Oj + 1).Address, "$")(1)      'Letra da coluna mais à esquerda
    Y = Split(Cells(1, Oj + C + 1).Address, "$")(1)  'Letra da coluna mais à direita
    
    For J = 1 To C
        'Etapa de ordenação das linhas pelos zeros da coluna
        For I = L To J + 1 Step -1
            If Cells(I + Oi, J + Oj) <> 0 And Cells(I + Oi - 1, J + Oj) = 0 Then
                'Eu modifiquei aqui para fazer trocar de intervalos com larguras definidas em vez de
                'recortar e colar uma linha inteira da planilha para inserir no final da matriz.
                
                'Copia a linha com o zero para 'Q'
                Q = Range(X & I + Oi - 1 & ":" & Y & I + Oi - 1).Value  'Perceba que tudo em Range() está concatenado para formar um intervalo (e.g. "A4:D4")
                
                'Copia as linhas de baixo para a posição da linha do zero (pode haver sobreposição)
                Range(X & I + Oi - 1 & ":" & Y & I + Oi - 1).Value = Range(X & I + Oi & ":" & Y & L + Oi).Value
                
                'Copia 'Q' (que tem a linha do zero) para a última linha da matriz
                Range(X & I + Oi & ":" & Y & L + Oi).Value = Q
            End If
        Next I
        
        'Etapa de escalonamento da matriz
        For I = L To J + 1 Step -1
            If Not Cells(I + Oi - 1, J + Oj) = 0 Then
                M = Cells(I + Oi, J + Oj) / Cells(I + Oi - 1, J + Oj)
                For K = J To C
                    Cells(I + Oi, K + Oj) = Cells(I + Oi, K + Oj) - Cells(I + Oi - 1, K + Oj) * M
                Next K
            End If
        Next I
    Next J
    
End Sub

Sub Criar()
    Oi = Range(Cells(2, 21)).Row - 1
    Oj = Range(Cells(2, 21)).Column - 1
    L = Cells(2, 12)
    C = Cells(2, 16)
    
    For I = 1 To L
        For J = 1 To C
            Cells(I + Oi, J + Oj) = WorksheetFunction.RandBetween(-7, 7)
        Next J
    Next I
    
    Range(Cells(1 + Oi, 1 + Oj), Cells(L + Oi, C + Oj)).NumberFormat = "0"
    Range(Cells(1 + Oi, 1 + Oj), Cells(L + Oi, C + Oj)).Font.Size = 10
    Range(Cells(1 + Oi, 1 + Oj), Cells(L + Oi, C + Oj)).HorizontalAlignment = xlCenter
    Range(Cells(1 + Oi, 1 + Oj), Cells(L + Oi, C + Oj)).VerticalAlignment = xlCenter
    
End Sub
