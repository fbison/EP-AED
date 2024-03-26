#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "controle_linhas.h"
#include "global_functions.h"

ListaLinhas* instanciaLista(){
    ListaLinhas * lista = malloc(sizeof(ListaLinhas));
    lista->lista= malloc(TAMANHO * sizeof(char*));
    lista->livre= 0;
    lista->tam= TAMANHO;
    return lista;
}

void adicionaLinha(ListaLinhas * lista, char * novaLinha){
    if(lista->tam== lista->livre){
        lista->tam= lista->tam + TAMANHO;
        lista->lista= realloc(lista->lista, (lista->tam) * sizeof(char*));
    }
    lista->lista[lista->livre]= novaLinha;
    lista->livre = lista-> livre + 1;
}

void destroi_listaLinhas(ListaLinhas *lista){
    int i;
    for(i=0; i< lista->livre; i++){
        free(lista->lista[i]);
    }
    free(lista->lista);
    free(lista);
}