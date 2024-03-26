#ifndef lista_ligada_h
#define lista_ligada_h

#define FALSE 0
#define TRUE 1

#define LISTA_LIGADA
//#define LISTA_ORDENADA

typedef int Boolean;

typedef struct _element_ {
	char * palavra;
	int * linhas;
	int quantidade;
	int quantidadeLinhas;
} Elemento;

typedef struct noLista {
	Elemento valor;
	struct noLista * proximo;
} NoLista;

typedef struct lista_ligada {
	NoLista * primeiro;
} ListaLigada;

ListaLigada * cria_lista();
void destroi_lista(ListaLigada * lista);
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
NoLista * busca(ListaLigada * lista, char* palavra);
Boolean insere(ListaLigada * lista, char* palavra, int linha);

//Boolean remove_elemento(ListaLigada * lista, char* palavra);
#endif