#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    int qtd_cidades;
    Grafo *dados;
    int *visitadas;
    Caminho *novoCaminho, *melhorCaminho;
    novoCaminho = ListaCria();
    melhorCaminho = ListaCria();
    int melhorDistancia;
    

    // Le a quantidade de cidades
    scanf("%d", &qtd_cidades);

    visitadas = (int *) malloc(qtd_cidades * sizeof(int));

    // Aloca a estrutura de dados do grafo
    dados = alocarGrafo(qtd_cidades);

    // Le os dados do grafo
    leGrafo(&dados);

    // Ordena as listas de adjacencias
    ordenaGrafo(dados);

    // Imprime as adjacencias do grafo
    imprimeGrafo(dados);

    // Inicia a busca pelo melhor caminho a partir da cidade 0
    encontraCaminho(dados, visitadas, 0, 0, novoCaminho, &melhorDistancia, melhorCaminho);

    // Imprime o melhor caminho encontrado e sua distancia
    imprimeCaminho(melhorCaminho, &melhorDistancia);

    // Libera a memoria alocada para as listas Caminho
    ListaDestroiCaminho(&novoCaminho);
    ListaDestroiCaminho(&melhorCaminho);

    // Libera a memoria alocada para o grafo
    desalocarGrafo(&dados);

    return 0;
}