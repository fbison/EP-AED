#include "indexar_arvore.h"

int* imprimeLinhasComPalavra(Arvore *arvore, ListaLinhas*  lista, char * palavra ){
    No * no = busca_bin(arvore, palavra);
    if(no != NULL && no->numAparicoes > 0 && no->linhas != NULL){    
        printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", no->numAparicoes, palavra);
        for (int i = 0; i < no->numAparicoes; i++)
        {
            if(no->linhas[i] != 0 && no->linhas[i] == no->linhas[i-1]) continue; //evita repetição de linhas    
            printf("%05d: %s\n", no->linhas[i], lista->lista[no->linhas[i]-1]);
        }
    }else{
        printf("Palavra '%s' nao encontrada.", palavra);
    }

}

Indexacao* indexarTexto(FILE* in){
    char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;	

    int contador_linha = 0;
 	linha = (char *) malloc((TAMANHO + 1) * sizeof(char));
    ListaLinhas* lista = instanciaLista();
    Arvore* arvore = cria_arvore();

    //mecanismo para manter a árvore mais balanceada
    insere_ord(arvore, "m", -1);
    arvore->raiz->numAparicoes = 0;
    arvore->raiz->linhas = NULL;
    char *delimiters = " -,.;:\u2013";  // Espaço, hífen, vírgula e travessão
        
    while(in && fgets(linha, TAMANHO, in)){
        if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;
            adicionaLinha(lista, strdup(linha));
        copia_ponteiro_linha = linha;
        while( (palavra = strsep(&copia_ponteiro_linha, delimiters)) ){
            if (palavra[0] != '\0' && strspn(palavra, " ") != strlen(palavra)) {
                insere_ord(arvore, copyToLower(palavra), contador_linha +1);
            }
        }        
        contador_linha++;
	};
    Indexacao * indexacao = (Indexacao*) malloc(sizeof(Indexacao));
    indexacao->arvore = arvore;
    indexacao->listaLinhas = lista; 
    return indexacao;
}
