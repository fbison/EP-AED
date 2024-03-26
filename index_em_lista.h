#ifndef index_em_lista_h
#define index_em_lista_h

#include <stdio.h>
#include "controle_linhas.h"
#include "lista_ligada.h"

typedef struct indexacaoLista
{
  ListaLigada * listaLigada;
  ListaLinhas * listaLinhas;
} IndexacaoLista;

IndexacaoLista * createList(FILE *  file);
void printListSearch(ListaLigada * listaLigada, ListaLinhas * listaLinhas, char * wordToFind);

#endif