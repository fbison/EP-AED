#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_ligada.h"

ListaLigada * cria_lista(){

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->primeiro = (NoLista *) malloc (sizeof(NoLista));
	lista->primeiro = NULL;

	return lista;
}

void destroi_lista(ListaLigada * lista){

	NoLista * p = lista->primeiro;
	NoLista * tmp;

	while(p){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(lista);
}

int tamanho(ListaLigada * lista){

	int tamanho = 0;

	NoLista * p = lista->primeiro;

	while(p){
		
		tamanho++;
		p = p->proximo;
	}

	return tamanho;
}

void imprime(ListaLigada * lista){

	NoLista * p;

	printf("Lista:");

	for(p = lista->primeiro; p; p = p->proximo){

		printf(" %s", p->valor.palavra);
	}

	printf("\n");
}

NoLista * busca(ListaLigada * lista, char * palavra){
	int i = 0;
	NoLista * p = lista->primeiro;

	while(p){
		if(strcmp(p->valor.palavra, palavra) == 0) return p;
		
		p = p->proximo;
		i++;
	}

	return NULL;
}

Boolean insere(ListaLigada * lista, char* palavra, int linha){

    NoLista * p;
    NoLista * anterior;
    NoLista * NoListavo = (NoLista*) malloc(sizeof(NoLista));

    NoListavo->valor.palavra = palavra;
    NoListavo->valor.quantidade = 1;
    NoListavo->valor.quantidadeLinhas = 1;
    NoListavo->valor.linhas = (int*)malloc(sizeof(int));

    anterior = NULL;

	p = lista->primeiro;
    if(p == NULL){
        NoListavo->proximo = lista->primeiro;
        lista->primeiro = NoListavo;
    } else {
        while(p){
            if(strcmp(palavra, p->valor.palavra) == 0) break;

            anterior = p;
            p = p->proximo;
        }
    }

	if(p != NULL && strcmp(palavra, p->valor.palavra) == 0) {
		p->valor.quantidade++;

		if (p->valor.quantidadeLinhas == 1 || p->valor.linhas[p->valor.quantidadeLinhas - 1] != linha) {
			p->valor.linhas =  realloc(p->valor.linhas, (p->valor.quantidadeLinhas + 1) * sizeof(int));
			p->valor.linhas[p->valor.quantidadeLinhas] = linha;
			p->valor.quantidadeLinhas++;
		}
	} else {
		NoListavo->proximo = p;

		if(anterior) anterior->proximo = NoListavo;
		else lista->primeiro = NoListavo;

		NoListavo->valor.linhas[0] = linha;
	}

    return TRUE;
}

// Boolean remove_elemento(ListaLigada * lista, char* palavra){

// 	int i;
// 	NoLista*  no =  busca(lista, palavra);;
// 	int indice = no->indice;
// 	NoLista * p;
// 	NoLista * tmp;

// 	if(indice >= 0) {

// 		if(indice == 0){

// 			tmp = lista->primeiro;
// 			lista->primeiro = tmp->proximo;
// 			free(tmp);
// 		}
// 		else{

// 			i = 0;
// 			p = lista->primeiro;

// 			while(p){

// 				if(i == indice - 1) break;

// 				i++;
// 				p = p->proximo;
// 			}
			
// 			tmp = p->proximo;
// 			p->proximo = p->proximo->proximo;
// 			free(tmp);
// 		}
		
// 		return TRUE;
// 	}

// 	return FALSE;
// }
