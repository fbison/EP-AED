#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h> 

#include "arvore_binaria.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Funções auxiliares. Não fazem parte do conjunto de operações elementares da estrutura //
///////////////////////////////////////////////////////////////////////////////////////////

Boolean __debug__ = FALSE;
void debug_on() { __debug__ = TRUE; }
void debug_off() { __debug__ = FALSE; }

#define ROWS 100
#define COLS 80

int display_rec(char ** buffer, No * no, int level, double h_position){
	char * ptr;
	int i, col, a, b;
	double offset;
	if(no){
		col = (int)(h_position * COLS);
		offset = 1.0 / pow(2, level + 2);

		ptr = buffer[1 + level * 3] + col;
		if(no->palavra != NULL){
			snprintf(ptr, COLS - col,  " %s  ", no->palavra);
		}
		*(ptr + strlen(ptr)) = ' ';

		if(no->esq || no->dir) *(buffer[2 + level * 3] + col + 1) = '|';

		if(no->esq){
		
			i = (int)((h_position - offset) * COLS);
			*(buffer[3 + level * 3] + 1 + i) = '|';
			i++;
			for(; i <= col; i++) *(buffer[3 + level * 3] + 1 + i) = '-';
		}
		
		if(no->dir){

			for(i = col; i < (int)((h_position + offset) * COLS); i++) *(buffer[3 + level * 3] + 1 + i) = '-';
			*(buffer[3 + level * 3] + 1 + i) = '|';
		}

		a = display_rec(buffer, no->esq, level + 1, h_position - offset);
		b = display_rec(buffer, no->dir, level + 1, h_position + offset);

		if(a > b) return a;
		return b;
	}
	
	return level;
}

void display_no(No * no){

	int i, j, r;

	char ** buffer = (char **) malloc(ROWS * sizeof(char *));

	for(i = 0; i < ROWS; i++) {

		buffer[i] = (char *) malloc((COLS + 1) * sizeof(char));

		for(j = 0; j < COLS; j++) buffer[i][j] = ' ';
		buffer[i][j] = '\0';
	}

	r = display_rec(buffer, no, 0, 0.5);

	if(__debug__) getchar();

	for(i = 0; i < 3 * r; i++) printf("%s\n", buffer[i]);
	printf("-----------------------------------------------------------------------------------------------\n");
}

void display(Arvore * arvore){
	
	if (arvore->raiz) {
        display_no(arvore->raiz);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementações comuns tanto para a árvore binária de "propósito geral", quanto para a árvore binária de busca //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Arvore * cria_arvore(){

	Arvore * arvore = (Arvore *) malloc (sizeof(Arvore));
	arvore->raiz = NULL;	
	return arvore;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void imprime_rec(No * no){

	// percurso in-ordem para a impressão dos char*s
	if(no){
		imprime_rec(no->esq);
		printf(" %s", no->palavra);
		imprime_rec(no->dir);
	}
}

void imprimeArvore(Arvore * arvore){

	printf("char*s na arvore:");
	imprime_rec(arvore->raiz);
	printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////
// Implementações específicas para a árvore binária de "propósito geral" (não ordenada) //
//////////////////////////////////////////////////////////////////////////////////////////

No * busca_rec(No * no, char* e){

	No * aux;

	if(no){

		if(__debug__) display_no(no);

		if(strcmp(no->palavra, e)==0) return no;

		aux = busca_rec(no->esq, e);
		if(aux) return aux;

		return busca_rec(no->dir, e);
	}
	return NULL;
}

No * buscaArvore(Arvore * arvore, char* e){
	
	return busca_rec(arvore->raiz, e);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Boolean insereNaArv(Arvore * arvore, No * pai, char* e, int lado){

	No * novo = (No *) malloc(sizeof(No));
	
	novo->palavra = e;
	novo->esq = novo->dir = NULL;

	if(!buscaArvore(arvore, e)){

		if(pai){

			if(lado == ESQUERDO){

				novo->esq = pai->esq;
				pai->esq = novo;
			}
			else{
				novo->esq = pai->dir;
				pai->dir = novo;
			}
		}
		else{
			novo->esq = arvore->raiz;
			arvore->raiz = novo;
		}

		return TRUE;
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Boolean remove_no_rec(Arvore * arvore, No * pai, No * no){

	No * a_remover;

	if(no){

		if(no->esq || no->dir){

			a_remover = no->esq ? no->esq : no->dir;
			no->palavra = a_remover->palavra;
			return remove_no_rec(arvore, no, a_remover);
		}
		else{

			if(pai) {

				if(pai->esq && pai->esq == no) pai->esq = NULL;
				if(pai->dir && pai->dir == no) pai->dir = NULL;
			}
			else{
				arvore->raiz = NULL;	
			}
				
			free(no);
			return TRUE;
		}
	}

	return FALSE;
}

No * encontra_pai(No * raiz, No * no){

	No * aux;

	if(raiz){

		if(raiz->esq == no) return raiz;
		if(raiz->dir == no) return raiz;

		aux = encontra_pai(raiz->esq, no);
		if(aux) return aux;

		return encontra_pai(raiz->dir, no);
	}

	return NULL;
}

Boolean remove_no(Arvore * arvore, No * no){

	return remove_no_rec(arvore, encontra_pai(arvore->raiz, no), no);
}

///////////////////////////////////////////////////////////////
// Implementações específicas para a árvore binária de busca //
///////////////////////////////////////////////////////////////

No * busca_bin_rec(No * no, char* e){

	if(no){

		if(__debug__) display_no(no);
		if(strcmp(no->palavra, e)== 0) return no;
		// se palavra for menor que o nó alfabeticamente
		if(strcmp(e, no->palavra)<0) return busca_bin_rec(no->esq, e);
		return busca_bin_rec(no->dir, e);
	}

	return NULL;
}

No * busca_bin(Arvore * arvore, char* e){
	return  busca_bin_rec(arvore->raiz, e);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Boolean insere_ord_rec(No * raiz, No * novo){
	if(strcmp(novo->palavra, raiz->palavra) != 0){

		if(strcmp(novo->palavra, raiz->palavra)<0){

			if(raiz->esq) return insere_ord_rec(raiz->esq, novo);
			else raiz->esq = novo;
		}
		else{
			if(raiz->dir) return insere_ord_rec(raiz->dir, novo);
			else raiz->dir = novo;
		}
	}else{
		raiz->numAparicoes= raiz->numAparicoes +1;
		raiz->linhas= realloc(raiz->linhas, raiz->numAparicoes * sizeof(int));
		raiz->linhas[raiz->numAparicoes-1] = novo->linhas[0];
		free(novo);
	}
	return TRUE;
}

Boolean insere_ord(Arvore * arvore, char* e, int numLinha){

	No * novo = (No *) malloc(sizeof(No));
	
	novo->palavra = e;
	novo->linhas = (int*)malloc(sizeof(int));
	novo->linhas[0] = numLinha;
	novo->numAparicoes=1;
	novo->esq = novo->dir = NULL;

	if(arvore->raiz) return insere_ord_rec(arvore->raiz, novo);
	arvore->raiz = novo;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

No * encontra_menor(No * raiz){

	if(raiz->esq) return encontra_menor(raiz->esq);
	
	return raiz;
}

No * encontra_maior(No * raiz){

	if(raiz->dir) return encontra_maior(raiz->dir);
	
	return raiz;
}

No * encontra_pai_ord(No * raiz, No * no){

	if(raiz){

		if(raiz->esq == no) return raiz;
		if(raiz->dir == no) return raiz;
		if(strcmp(no->palavra, raiz->palavra) < 0) return encontra_pai_ord(raiz->esq, no);
		if(strcmp(no->palavra, raiz->palavra) > 0) return encontra_pai_ord(raiz->dir, no);
	}
		
	return NULL;
}

Boolean remove_ord(Arvore * arvore, No * no){

	Boolean retorno;
	char* valor_promovido;

	No * a_remover;
	No * pai;

	if(no){

		if(no->dir || no->esq){

			// Obs: só podemos efetuar a "promoção" do valor contido em "a_remover" 
			// após o termino da chamada recursiva. Caso contrário, uma eventual chamada
			// a "encontra_pai_ord" em alguma das chamadas recursivas encadeadas irá
			// retornar resultado inconsistente (devido a existência de valores duplicados 
			// na árvore). 

			a_remover = no->dir ? encontra_menor(no->dir) : encontra_maior(no->esq);
			valor_promovido = a_remover->palavra;
			retorno = remove_ord(arvore, a_remover);
			no->palavra = valor_promovido;
			return retorno;
		}
		else{
			pai = encontra_pai_ord(arvore->raiz, no);
			
			if(pai){
				if(pai->esq && pai->esq == no) pai->esq = NULL;
				if(pai->dir && pai->dir == no) pai->dir = NULL;
			}
			else{
				arvore->raiz = NULL;
			}

			free(no);
			return TRUE;
		}
	}

	return FALSE;
}

