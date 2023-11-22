#ifndef grafo_h
#define grafo_h
#define MAX_DIST 9999 // Valor maximo escolhido para distancias

#include <stdio.h>

typedef struct grafo Grafo;

struct grafo
{
    int qtd_cidades;    // Armazena o numero de cidades do grafo
    int **adj;          // Matriz de adjacencias
    int *visitadas;     // Vetor com as cidades ja visitadas
    int **distancias;   // Matriz que armazena as distancias entre as cidades
    int *novoCaminho;   // Vetor para armazenar o novo caminho
    int *melhorCaminho; // Vetor que armazena o melhor caminho entre as cidades
    int melhorPeso;     // Armazena o peso do melhor caminho
};

Grafo *alocarGrafo(int); // Funcao para alocar a estrutura do grafo

void desalocarGrafo(Grafo **); // Funcao para liberar a memoria alocada para o grafo

void leGrafo(Grafo **); // Funcao para ler o grafo a partir da entrada padrao

void encontraCaminho(Grafo *dados, int *visitadas, int passos, int cidadeAtual); // Funcao para encontrar o melhor caminho entre as cidades

void imprimeCaminho(Grafo *dados); // Funcao que imprime o melhor caminho

// Funcoes auxiliares

int calculaCaminho(int qtd_cidades, Grafo dados); // Funcao que calcula a distancia de cada caminho

#endif