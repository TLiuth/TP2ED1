#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

Grafo *alocarGrafo(int qtd_cidades)
{
    Grafo *dados;

    dados = (Grafo *)malloc(sizeof(Grafo));

    dados->qtd_cidades = qtd_cidades;

    // Aloca a matriz de adjacencias que representa as cidades e as distancias entre elas
    dados->adj = (int **)malloc(sizeof(int *) * qtd_cidades * qtd_cidades);
    for (int i = 0; i < qtd_cidades * qtd_cidades; i++)
    {
        dados->adj[i] = (int *)malloc(sizeof(int) * 3);
    }

    // Aloca o vetor que registra as cidades ja visitadas
    dados->visitadas = (int *)calloc(qtd_cidades, sizeof(int));

    // Aloca os vetores que armazenam todos os caminhos e o melhor caminho
    dados->novoCaminho = (int *)malloc(sizeof(int) * (qtd_cidades + 1));
    dados->melhorCaminho = (int *)malloc(sizeof(int) * (qtd_cidades + 1));

    // Aloca a matriz que contem apenas as distancias entre as cidades
    dados->distancias = (int **)malloc(sizeof(int *) * qtd_cidades);
    for (int i = 0; i < qtd_cidades; i++)
    {
        dados->distancias[i] = (int *)malloc(sizeof(int) * qtd_cidades);
    }

    int linhas = 1;

    for (int i = 1; i < qtd_cidades; i++)
    {
        linhas *= i;
    }

    return dados;
}

void desalocarGrafo(Grafo **dados)
{
    // Desaloca a matriz de adjacencias
    for (int i = 0; i < (*dados)->qtd_cidades * (*dados)->qtd_cidades; i++)
    {
        free((*dados)->adj[i]);
    }
    free((*dados)->adj);

    // Desaloca o vetor de cidades visitadas
    free((*dados)->visitadas);

    // Desaloca a matriz de distancias
    for (int i = 0; i < (*dados)->qtd_cidades; i++)
    {
        free((*dados)->distancias[i]);
    }
    free((*dados)->distancias);

    // Desaloca os vetores de caminhos
    free((*dados)->novoCaminho);
    free((*dados)->melhorCaminho);

    // Desaloca a estrutura principal
    free(*dados);

    *dados = NULL;
}

void leGrafo(Grafo **dados)
{
    // Le as cidades e as respectivas distancias
    for (int i = 0; i < (*dados)->qtd_cidades * (*dados)->qtd_cidades; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &(*dados)->adj[i][j]);
        }
    }

    int a = 0;

    // Reorganiza as adjacencias numa nova matriz para facilitar o acesso aos valores
    for (int i = 0; i < (*dados)->qtd_cidades; i++)
    {
        for (int j = 0; j < (*dados)->qtd_cidades; j++)
        {
            (*dados)->distancias[i][j] = (*dados)->adj[a][2];
            a++;
        }
    }
    
   /* for(int i = 0; i < (*dados)->qtd_cidades * (*dados)->qtd_cidades; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", (*dados)->adj[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for(int i = 0; i < (*dados)->qtd_cidades; i++){
        for(int j = 0; j < (*dados)->qtd_cidades; j++){
            printf("%d ", (*dados)->distancias[i][j]);
        }
        printf("\n");
    }*/
}

void encontraCaminho(Grafo *dados, int *visitadas, int passos, int cidadeAtual)
{
    static int melhorDistancia = INT_MAX;
    int distanciaTemp;
    dados->novoCaminho[passos] = cidadeAtual;
    passos++;

    if (passos == dados->qtd_cidades)
    {   
        // Calcula a distancia total do caminho atual
        distanciaTemp = calculaCaminho(dados->qtd_cidades, *dados);
        
        if (distanciaTemp < melhorDistancia)
        {
            melhorDistancia = distanciaTemp;
            dados->melhorPeso = melhorDistancia;

            //Armazena o melhor caminho encontrado ate o momento
            for (int i = 0; i < dados->qtd_cidades; i++)
            {
                dados->melhorCaminho[i] = dados->novoCaminho[i];
            }
        }
        
    }
    else
    {   
        // Atualiza a cidade atual como ja visitada
        visitadas[cidadeAtual] = 1;
        for (int proximaCidade = 0; proximaCidade < dados->qtd_cidades; proximaCidade++)
        {
            if (!visitadas[proximaCidade])
            {   
                // Recursivamente procura a proxima cidade
                encontraCaminho(dados, visitadas, passos, proximaCidade);
            }
        }
        // Atualiza novamente a cidade para nao visitada
        visitadas[cidadeAtual] = 0;
    }

    
}


int calculaCaminho(int qtd_cidades, Grafo dados)
{
    int total = 0;

    // Calcula a distancia do caminho dado
    for (int i = 0; i < qtd_cidades; i++)
    {
        if(dados.distancias[dados.novoCaminho[i]][dados.novoCaminho[i + 1]] == 0) 
            return 1000; // Valor de retorno utilizado para esta condicao nao entrar na verificacao

        total += dados.distancias[dados.novoCaminho[i]][dados.novoCaminho[i + 1]];
    }
    return total;
}

void imprimeCaminho(Grafo *dados){

    dados->melhorCaminho[dados->qtd_cidades] = 0;

    // Imprime o melhor caminho
    for(int i = 0; i <= dados->qtd_cidades; i++){
        printf("%d ", dados->melhorCaminho[i]);
    }

    // Imprime a distancia do melhor caminho
    printf("\n%d", dados->melhorPeso);

}