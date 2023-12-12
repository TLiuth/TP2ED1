#ifndef grafo_h
#define grafo_h
#define MAX_DIST 9999 // Valor maximo escolhido para distancias

#include <stdio.h>
#include <stdbool.h>

typedef struct grafo Grafo;

typedef struct celula Celula;

typedef struct item Item;

<<<<<<< Updated upstream

=======
typedef struct caminho Caminho;

// Definicao da da estrutura do grafo
>>>>>>> Stashed changes
struct grafo
{
    Celula **cabeca; // Vetor de ponteiros para as cabecas das listas encadeadas
    Celula **ultimo; // Vetor de ponteiros para os ultimos elementos das listas encadeadas
    int numCidades; // Numero total de cidades no grafo
};

// Definicao da estutura da celula da lista encadeada
struct celula
{
    struct celula *prox; // Ponteiro para a proxima celula
    Item *item; // Ponteiro para o item da celula
    int tam; // Armazena o tamanho da lista
};

// Definicao da estrutura de um item da lista
struct item
{
    int cidade; 
    int distancia;
};

<<<<<<< Updated upstream
=======
// Definicao da estrutura de um caminho como lista encadeada
struct caminho 
{
    Celula *cabeca; // Ponteiro para a cekula cabeca da lista
    Celula *ultimo; // Ponteiro para o ultimo elemento da lista
};

>>>>>>> Stashed changes


Grafo *alocarGrafo(int); // Funcao para alocar a estrutura do grafo

void desalocarGrafo(Grafo **); // Funcao para liberar a memoria alocada para o grafo

void leGrafo(Grafo **); // Funcao para ler o grafo a partir da entrada padrao

void encontraCaminho(Grafo *dados, int *visitadas, int passos, int cidadeAtual); // Funcao para encontrar o melhor caminho entre as cidades

<<<<<<< Updated upstream
void imprimeCaminho(Grafo *dados); // Funcao que imprime o melhor caminho

void imprimeGrafo(Grafo *dados);

bool ListaGet(Grafo *gp, int pos, int p, Item *pX);

int ListaTamanho(Grafo* gp, int index);

void ListaDestroi(Celula** pLista);

// Funcoes auxiliares

int calculaCaminho(int qtd_cidades, Grafo dados); // Funcao que calcula a distancia de cada caminho
=======
void imprimeCaminho(Caminho *caminho, int *melhorPeso); // Funcao que imprime o melhor caminho

void imprimeGrafo(Grafo *dados); // Funcao que imprime as adjancencias do grafo

int ListaTamanho(Grafo* gp, int index); // Funcao que retorna o tamanho de uma lista em uma posicao especifica no grafo

void ListaDestroi(Celula** pLista); // Funcao que destroi uma lista encadeada

bool ListaEhVazia(Caminho *caminho); // Funcao que verifica se uma lista esta vazia

void ListaDestroiCaminho(Caminho** pLista); // Funcao que destroi uma lista Caminho

bool ListaRetiraFinal(Caminho* pLista); // Funcao que retira o ultimo elemento de uma lista

bool ListaInsereFinalCaminho(Caminho* pLista, int x); // Funcao que insere um elemento no final da lista

void ListaLimpa(Caminho *lista); // Funcao que limpa os elementos de uma lista

void ListaCopia(Caminho *origem, Caminho *destino); // Funcao que copia os elementos de uma lista para outra

bool ListaGet(Grafo *gp, int pos, Item *pX, int destino); // Funcao que obtem um item de uma lista em uma posicao especifica no grafo


// Funcoes auxiliares

Caminho* ListaCria(); // Funcao que cria uma lista Caminho vazia

int calculaCaminho(int qtd_cidades, Grafo *dados, Caminho *caminho); // Funcao que calcula a distancia de cada caminho
>>>>>>> Stashed changes

void ordenaLista(Celula** head); // Funcao que ordena uma lista encadeada

void ordenaGrafo(Grafo* dados); // Funcao que ordena todas as listas presentes no grafo

void troca(Celula* cel1, Celula* cel2); // Funcao que realiza a troca de dois elementos na lista

#endif