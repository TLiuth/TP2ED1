#ifndef grafo_h
#define grafo_h
#define MAX_DIST 9999 // Valor maximo escolhido para distancias

#include <stdio.h>
#include <stdbool.h>

typedef struct grafo Grafo;

typedef struct celula Celula;

typedef struct item Item;


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



Grafo *alocarGrafo(int); // Funcao para alocar a estrutura do grafo

void desalocarGrafo(Grafo **); // Funcao para liberar a memoria alocada para o grafo

void leGrafo(Grafo **); // Funcao para ler o grafo a partir da entrada padrao

void encontraCaminho(Grafo *dados, int *visitadas, int passos, int cidadeAtual); // Funcao para encontrar o melhor caminho entre as cidades

void imprimeCaminho(Grafo *dados); // Funcao que imprime o melhor caminho

void imprimeGrafo(Grafo *dados);

bool ListaGet(Grafo *gp, int pos, int p, Item *pX);

int ListaTamanho(Grafo* gp, int index);

void ListaDestroi(Celula** pLista);

// Funcoes auxiliares

int calculaCaminho(int qtd_cidades, Grafo dados); // Funcao que calcula a distancia de cada caminho

#endif