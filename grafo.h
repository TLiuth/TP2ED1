#ifndef grafo_h
#define grafo_h
#define MAX_DIST 9999 // Valor maximo escolhido para distancias

#include <stdio.h>
#include <stdbool.h>

typedef struct grafo Grafo;

typedef struct celula Celula;

typedef struct item Item;

typedef struct caminho Caminho;


struct grafo
{
    Celula **cabeca;
    Celula **ultimo;
    int numCidades;
};

struct celula
{
    struct celula *prox;
    Item *item;
    int tam;
};

struct item
{
    int cidade;
    int distancia;
};

struct caminho 
{
    Celula *cabeca;
    Celula *ultimo;
};



Grafo *alocarGrafo(int); // Funcao para alocar a estrutura do grafo

void desalocarGrafo(Grafo **); // Funcao para liberar a memoria alocada para o grafo

void leGrafo(Grafo **); // Funcao para ler o grafo a partir da entrada padrao

void encontraCaminho(Grafo *dados, int *visitadas, int passos, int cidadeAtual, Caminho *novoCaminho, int *melhorPeso, Caminho *melhorCaminho); // Funcao para encontrar o melhor caminho entre as cidades

void imprimeCaminho(Caminho *caminho, int *melhorPeso); // Funcao que imprime o melhor caminho

// Funcoes auxiliares

void imprimeGrafo(Grafo *dados);

int ListaTamanho(Grafo* gp, int index);

void ListaDestroi(Celula** pLista);

bool ListaEhVazia(Caminho *caminho);

void ListaDestroiCaminho(Caminho** pLista);

bool ListaRetiraFinal(Caminho* pLista);

bool ListaInsereFinalCaminho(Caminho* pLista, int x);

void ListaLimpa(Caminho *lista);

void ListaCopia(Caminho *origem, Caminho *destino);

bool ListaGet(Grafo *gp, int pos, Item *pX, int destino);

Caminho* ListaCria();

int calculaCaminho(int qtd_cidades, Grafo *dados, Caminho *caminho); // Funcao que calcula a distancia de cada caminho

void ordenaLista(Celula** head);

void ordenaGrafo(Grafo* dados);

void troca(Celula* cel1, Celula* cel2);

#endif