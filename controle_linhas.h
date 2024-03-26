#ifndef controle_linhas_h
#define controle_linhas_h



typedef struct lista_linhas{
    char ** lista;
    int livre;
    int tam;
} ListaLinhas;

ListaLinhas* instanciaLista();
void adicionaLinha(ListaLinhas * lista, char * novaLinha);
void destroi_listaLinhas(ListaLinhas *lista);

#endif