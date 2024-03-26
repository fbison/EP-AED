#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "lista_sequencial_ordenada.h"

#include "lista_ligada.h"
#include "index_em_lista.h"
#include "global_functions.h"

char** linhas;

IndexacaoLista * createList(FILE *  file) {
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;	
	char * copia_ponteiro_palavra;
	int contador_linha = 0;

	ListaLigada * lista = cria_lista();
	ListaLinhas* linhas = instanciaLista();
	linha = (char *) malloc((TAMANHO + 1) * sizeof(char));
	char *delimiters = " -,.;:\u2013";  // Espaço, hífen, vírgula e travessão

	while(file && fgets(linha, TAMANHO, file)){			
		if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

		adicionaLinha(linhas, strdup(linha));		
		copia_ponteiro_linha = strdup(linha);

		while((palavra = strsep(&copia_ponteiro_linha, delimiters))){
			if(palavra[0] != '\0' && strspn(palavra, " ") != strlen(palavra))
				insere(lista, copyToLower(palavra), contador_linha + 1);
		}

		contador_linha++;
	}

	IndexacaoLista * indexacao = (IndexacaoLista*) malloc(sizeof(IndexacaoLista));
	indexacao->listaLigada = lista;
	indexacao->listaLinhas = linhas; 

	return indexacao;
}

void printListSearch(ListaLigada * listaLigada, ListaLinhas * listaLinhas, char * wordToFind) {
	NoLista * no = busca(listaLigada, wordToFind);

	if(no == NULL) {
		printf("Palavra '%s' nao encontrada\n", wordToFind);
		return;
	}

	Elemento element = no->valor;

	printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", element.quantidade, element.palavra);

	for (int i = 0; i < element.quantidadeLinhas; i++)
        printf("%05d: %s\n", element.linhas[i], listaLinhas->lista[element.linhas[i]-1]);

	return;
}