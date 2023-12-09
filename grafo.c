#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"


Grafo *alocarGrafo(int qtd_cidades)
{
    Grafo *gp = malloc(sizeof(Grafo));
    gp->numCidades = qtd_cidades;
    gp->cabeca = malloc(qtd_cidades * sizeof(Celula*)); //Aloca um vetor de ponteiros para listas encadeadas
    gp->ultimo = malloc(qtd_cidades * sizeof(Celula*)); //Aloca um vetor de ponteiros para os últimos elementos das listas encadeadas
    for(int i = 0; i < qtd_cidades; i++){
        gp->cabeca[i] = malloc(sizeof(Celula)); // aloca memória para uma única celula, que será a cabeça da lista propriamente dita
        gp->ultimo[i] = gp->cabeca[i]; // o ponteiro de último aponta para o mesmo endereço que o ponteiro da cabeça (não há elementos na lista ainda)
        gp->cabeca[i]->tam = 0; // inicia o tamanho da lista como zero
        gp->cabeca[i]->prox = NULL; // o próximo da celula cabeça é NULL
        gp->cabeca[i]->item = NULL; // Não há itens
        //O objetivo de inicializar a cabeça é armazenar o tamanho das listas
        //As demais células terão o campo tam, mas esse não será utilzado
    }
    
    return gp;
}

bool ListaInsereFinal(Grafo *gp, Item x, int pos) {
    Celula* nova = malloc(sizeof(Celula));
    nova->item = malloc(sizeof(Item)); 
    if (nova == NULL)
        return false;
    *(nova->item) = x;
    nova->prox = NULL;
    if (gp->ultimo[pos] != NULL)
        gp->ultimo[pos]->prox = nova;
    else
        gp->cabeca[pos] = nova;
    gp->ultimo[pos] = nova;
    (*gp->cabeca[pos]).tam++;
    return true;
}



void desalocarGrafo(Grafo **dados)
{
    for(int i = 0; i < (*dados)->numCidades; i++){
            ListaDestroi(&((*dados)->cabeca[i]));;
    }
    free((*dados)->cabeca);
    free((*dados)->ultimo);
    free(*dados);
    *dados = NULL;

}

void ListaDestroi(Celula** celula) {
    Celula* aux = *celula, *aux1;
    while (aux != NULL) {
        aux1 = aux->prox;
        if (aux->item != NULL) {
            free(aux->item);
        }
        free(aux);
        aux = aux1;
    }
    *celula = NULL;
}

void leGrafo(Grafo **dados)
{
    int origem;
    Item aux;
    for(int i = 0; i < (*dados)->numCidades; i++){
        for(int j = 0; j < (*dados)->numCidades; j++){
            scanf("%d%d%d", &origem, &aux.cidade, &aux.distancia);
            ListaInsereFinal(*dados, aux, origem);
            
        }
    }
}


bool ListaGet(Grafo *gp, int pos, int p, Item *pX) {
    if (p >= ListaTamanho(gp, pos) || p < 0 )
        return false;
    Celula* aux = gp->cabeca[pos];
    for (int i=0;i<p;i++)
        aux = aux->prox;
    if (aux->item != NULL){
        (*pX) = *(aux->item);
    }
    
    return true;
}


void imprimeGrafo(Grafo *dados)
{
    Item aux;
    Celula *p; // pointer to traverse the list
    for(int i = 0; i < (dados)->numCidades; i++){
        p = dados->cabeca[i]->prox; // point to the first element of the list
        printf("Adjacencias do vertice %d: ", i);
        while (p != NULL) { // while not at the end of the list
            aux = *(p->item); // get the item
            printf("(%d ,%d) -> ", aux.cidade, aux.distancia); // print it
            p = p->prox; // move to the next element
        }
        printf("NULL\n"); // print a newline after each list
    }
}

int ListaTamanho(Grafo* gp, int index) {
    return gp->cabeca[index]->tam;
}

void ordenaGrafo(Grafo* dados){
    for(int i = 0; i < dados->numCidades; i++){
        ordenaLista(&(dados->cabeca[i]));
    }
}

void ordenaLista(Celula** head) {
    // Check if list is empty or contains only one element
    if (*head == NULL || (*head)->prox == NULL) {
        return;
    }

    Celula *aux = (*head)->prox, *aux1;

    while (aux != NULL) {
        aux1 = aux->prox;
        while(aux1 != NULL){
            if(aux->item->distancia > aux1->item->distancia){
                troca(aux, aux1);
            }
            aux1 = aux1->prox;
        }
        aux = aux->prox;
    }
}

// void ordenaLista(Celula** head) {
//     // Check if list is empty or contains only one element
//     if (*head == NULL || (*head)->prox == NULL) {
//         return;
//     }

//     Celula *aux = *head, *aux1;

//     while (aux != NULL) {
//         aux1 = aux->prox;
//         while(aux1 != NULL){
//             if(aux->item->distancia > aux1->item->distancia){
//                 troca(aux, aux1);
//             }
//             aux1 = aux1->prox;
//         }

//          aux = aux->prox;
//     }
// }

void troca(Celula* cel1, Celula* cel2){
    Item aux = (*cel1->item);
    (*cel1->item) = (*cel2->item);
    (*cel2->item) = aux;
    
}

// bool ListaInsereInicio(Grafo *gp, Item x, int pos){
//     Celula *nova = malloc(sizeof(Celula));
//     nova->item = malloc(sizeof(Item));
//     if (nova == NULL) return false;
//     *(nova->item) = x;
//     nova->prox = gp->cabeca[pos]->prox; // make nova point to the first element of the list 
//     gp->cabeca[pos]->prox = nova; // make cabeca point to nova 
//     if (gp->ultimo[pos] == gp->cabeca[pos]) // if the list was empty, make ultimo point to nova as well
//     gp->ultimo[pos] = nova;
//     (*gp->cabeca[pos]).tam++;
//     return true;
//     }


// void encontraCaminho(Grafo *dados, int *visitadas, int passos, int cidadeAtual)
// {
//     static int melhorDistancia = INT_MAX;
//     int distanciaTemp;
//     dados->novoCaminho[passos] = cidadeAtual;
//     passos++;

//     if (passos == dados->qtd_cidades)
//     {   
//         // Calcula a distancia total do caminho atual
//         distanciaTemp = calculaCaminho(dados->qtd_cidades, *dados);
        
//         if (distanciaTemp < melhorDistancia)
//         {
//             melhorDistancia = distanciaTemp;
//             dados->melhorPeso = melhorDistancia;

//             //Armazena o melhor caminho encontrado ate o momento
//             for (int i = 0; i < dados->qtd_cidades; i++)
//             {
//                 dados->melhorCaminho[i] = dados->novoCaminho[i];
//             }
//         }
        
//     }
//     else
//     {   
//         // Atualiza a cidade atual como ja visitada
//         visitadas[cidadeAtual] = 1;
//         for (int proximaCidade = 0; proximaCidade < dados->qtd_cidades; proximaCidade++)
//         {
//             if (!visitadas[proximaCidade])
//             {   
//                 // Recursivamente procura a proxima cidade
//                 encontraCaminho(dados, visitadas, passos, proximaCidade);
//             }
//         }
//         // Atualiza novamente a cidade para nao visitada
//         visitadas[cidadeAtual] = 0;
//     }

    
// }


// int calculaCaminho(int qtd_cidades, Grafo dados)
// {
//     int total = 0;

//     // Calcula a distancia do caminho dado
//     for (int i = 0; i < qtd_cidades; i++)
//     {
//         if(dados.distancias[dados.novoCaminho[i]][dados.novoCaminho[i + 1]] == 0) 
//             return 1000; // Valor de retorno utilizado para esta condicao nao entrar na verificacao

//         total += dados.distancias[dados.novoCaminho[i]][dados.novoCaminho[i + 1]];
//     }
//     return total;
// }

// void imprimeCaminho(Grafo *dados){

//     dados->melhorCaminho[dados->qtd_cidades] = 0;

//     // Imprime o melhor caminho
//     for(int i = 0; i <= dados->qtd_cidades; i++){
//         printf("%d ", dados->melhorCaminho[i]);
//     }

//     // Imprime a distancia do melhor caminho
//     printf("\n%d", dados->melhorPeso);

// }