
#include "controle_linhas.h"
#include "global_functions.h"
#include "arvore_binaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct  indexacao
{
    Arvore * arvore;
    ListaLinhas * listaLinhas;
} Indexacao;

int* imprimeLinhasComPalavra(Arvore *arvore, ListaLinhas*  lista, char * palavra );
Indexacao* indexarTexto(FILE* in);