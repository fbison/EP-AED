# Motivação:
    Aprender na prática como implementar e utilizar estruturas de dado do tipo lista e árvore. 
    Para isso implementamos um indexador e buscador de palavras para arquivos de texto to tipo 
    .txt, dando ao usuário a opção de utilizar lista ou árvore binária de busca como estrutura 
    para armazenar os dados (palavras).

# Sobre o Programa:
    O programa, ao ser executado no terminal, recebe dois parâmetros. O primeiro define o 
    nome do arquivo texto a ser indexado, e sobre o qual as buscas serão feitas. O segundo
    parâmetro define o tipo de estrutura a ser empregada para representar o índice na execução
    atual. As únicas opções válidas para este segundo parâmetro são: lista ou arvore.
   
    O programa retornará, então, o número total de linhas e o tempo total de indexação de
    acordo com a estrutura de dado selecionada.

    Após a carga do arquivo de texto e construção do índice, o programa imprime "> ", indicando
    que  está esperando algum comando do usuário. O usuário pode então executar dois “comandos”
    possíveis: o comando “busca palavra” (onde palavra deve ser subsutituída pelo termo que deseja
    buscar) ou o comando “fim” (que encerra o programa). Enquanto a segunda opção não for utilizada,
    o programa segue aguardando novos comandos.

    Observações: o sistema não faz diferenciação entre letras maiúsculas e minúsculas
                 a busca é sempre feita utilizando palavras inteiras (singular != plural)
                 palavras compostas por hífen são tratadas como palavras diferentes

# Como Compilar:
    (1) Através do Terminal, vá até a pasta em que os arquivos estão localizados.

    (2) Execute a seguinte linha de comando:
            
            gcc epaed.c global_functions.c lista_ligada.c index_em_lista.c controle_linhas.c arvore_binaria.c indexar_arvore.c -lm -o meuPrograma

    (3) Agora, foi criado um executável com o nome "meuPrograma", basta fornecer os parametros, por exemplo:

            ./meuPrograma teste.txt lista
            ./meuPrograma teste.txt arvore

    (4) Basta inserir os comandos desejados, como explicado no tópico "Sobre o Programa".

# Bibliotecas Utilizadas
    controle_linha.h
        Responsável por salvar as linhas em uma lista sequencial estática 

    arvore_binaria.h
        Responsável pela organização da estrutura de árvore binária, sua busca, organização e display

    indexar_arvore.h
        Percorre o arquivo indexando em uma árvore binária e realizando a impressão no caso de busca
    
    index_em_linha.h
         Percorre o arquivo indexando em uma lista ligada e realizando a impressão no caso de busca
    
    global_functions.h
        Declara funções úteis em todo o código, como copyToLower e srtsep

# Autores do Programa
    Filipe Bison de Souza        NUSP 14570653
    Pedro Losso Quintans         NUSP 14603120
    Rodrigo Gonçalves Cardoso    NUSP 14658330