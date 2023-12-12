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

<<<<<<< Updated upstream
    // Inicia a busca pelo melhor caminho a partir da cidade 0
    // encontraCaminho(dados, dados->visitadas, 0, 0);

    // Imprime o melhor caminho encontrado e sua distancia
    // imprimeCaminho(dados);

=======
    // Ordena as listas de adjacencias
>>>>>>> Stashed changes
    ordenaGrafo(dados);

    // Imprime as adjacencias do grafo
    imprimeGrafo(dados);

<<<<<<< Updated upstream
    // Libera a memoria alocada
=======
    // Inicia a busca pelo melhor caminho a partir da cidade 0
    encontraCaminho(dados, visitadas, 0, 0, novoCaminho, &melhorDistancia, melhorCaminho);

    // Imprime o melhor caminho encontrado e sua distancia
    imprimeCaminho(melhorCaminho, &melhorDistancia);

    // Libera a memoria alocada para as listas Caminho
    ListaDestroiCaminho(&novoCaminho);
    ListaDestroiCaminho(&melhorCaminho);

    // Libera a memoria alocada para o grafo
>>>>>>> Stashed changes
    desalocarGrafo(&dados);

    return 0;
}