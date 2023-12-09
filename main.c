#include <stdio.h>
#include "grafo.h"

int main()
{
    int qtd_cidades;
    Grafo *dados;

    // Le a quantidade de cidades
    scanf("%d", &qtd_cidades);

    // Aloca a estrutura de dados do grafo
    dados = alocarGrafo(qtd_cidades);

    // Le os dados do grafo
    leGrafo(&dados);

    // Inicia a busca pelo melhor caminho a partir da cidade 0
    // encontraCaminho(dados, dados->visitadas, 0, 0);

    // Imprime o melhor caminho encontrado e sua distancia
    // imprimeCaminho(dados);

    imprimeGrafo(dados);

    // Libera a memoria alocada
    desalocarGrafo(&dados);

    return 0;
}