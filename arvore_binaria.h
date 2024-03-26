#ifndef arvore_binaria_h
#define arvore_binaria_h

#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef int Boolean;

typedef struct _no_arvore_ {

	char* palavra;
	int * linhas;
	int numAparicoes;
	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;

} No;

typedef struct {

	No * raiz;

} Arvore;

Arvore * cria_arvore();
void imprimeArvore(Arvore * arvore);

// Se a ideia é usar a árvore binária como uma árvore
// de "propsito geral", sem organizar os elementos
// pelos seus valores, use as funções abaixo:

No * buscaArvore(Arvore * arvore, char* e);
Boolean insereNaArv(Arvore * arvore, No * pai, char* e, int lado);
Boolean remove_no(Arvore * arvore, No * no);

// Já se o objetivo é usar a árvore binária como uma
// árvore binária de busca (ABB), em que os elementos
// são organizados por ordem de valor, use as seguintes
// funções:

No * busca_bin(Arvore * arvore, char* e);
Boolean insere_ord(Arvore * arvore, char* e, int numLinha);
Boolean remove_ord(Arvore * arvore, No * no);

////////////////////////////////////////////////////////////////////////////////

// funções auxiliares para exibição da árvore, fora
// do conjunto de operações elementares da estrutura.

void display(Arvore * arvore);
void debug_on();
void debug_off();

#endif

