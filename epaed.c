#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <locale.h>
#include "index_em_lista.h"
#include "indexar_arvore.h"

#define TAMANHO 1000

void __fpurge(FILE *stream); //declarando função para eliminar o warning

char *strlwr(char *str)     //tivemos que copiar manualmente a função, estava dando erro de compilação
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}

void imprimeCabecalho(char * tipo, char * texto, int numLinhas, double tempo){
    printf("Tipo de indice: '%s'\n", tipo);
    printf("Arquivo de texto: '%s'\n", texto);
    printf("Numero de linhas no arquivo: %d\n", numLinhas);
    printf("Tempo para carregar o arquivo e construir o indice: %f ms\n", tempo);      
    printf ("> ");
}

double calculaTempo(clock_t begin){
    clock_t end = clock();
    return ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;    
}
void imprimeTempoBusca(clock_t begin){  
    printf("Tempo de busca: %f ms\n", calculaTempo(begin));
}

int main(int argc, char **argv)
{

    FILE *in;
    double time_spent = 0;
	clock_t begin, end;
    char comando[10];
    char palavra[60];
    setlocale(LC_ALL,"");

    if (argc == 3)
    {
        in = fopen(argv[1], "r");
        
        begin = clock();

        if (strcmp(argv[2], "lista") == 0)
        {    
            IndexacaoLista * indexacao = createList(in);

            imprimeCabecalho(argv[2], argv[1], indexacao->listaLinhas->livre, calculaTempo(begin));
            scanf("%s", comando);

            while ((strcmp(comando, "fim") != 0))
            {
                 if (strcmp(comando, "busca") == 0)
                {
                    scanf("%s", palavra);
                    begin = clock(); 

                    printListSearch(indexacao->listaLigada, indexacao->listaLinhas, strlwr(palavra));

                    imprimeTempoBusca(begin);
                }
                else
                {
                    printf("Opcao Invalida!\n");
                    __fpurge(stdin);

                }
                printf("> ");
                scanf("%s", comando);
            } 
        }
        else if (strcmp(argv[2], "arvore") == 0)
        {
            Indexacao* indexacao= indexarTexto(in);

            imprimeCabecalho(argv[2], argv[1], indexacao->listaLinhas->livre, calculaTempo(begin));

            scanf("%s", comando);

            while ((strcmp(comando, "fim") != 0))
            {
                 if (strcmp(comando, "busca") == 0)
                {
                    scanf("%s", palavra);
                    begin = clock(); 

                    imprimeLinhasComPalavra(indexacao->arvore, indexacao->listaLinhas, strlwr(palavra));

                    imprimeTempoBusca(begin); 
                }
                else
                {
                    printf("Opcao Invalida!\n");
                    __fpurge(stdin);
                }
                printf("> ");
                scanf("%s", comando);
            } 
        }
        return 0;
    }
    return 1;
}
