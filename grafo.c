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

void imprimeCaminho(Caminho* caminho, int *melhorPeso) {
    
    printf("Melhor caminho : ");
    Celula* aux = caminho->cabeca->prox;
    while (aux != NULL) {
        printf("%d ", aux->item->cidade);
        aux = aux->prox;
    }
    printf("\nMelhor distancia : %d\n", *melhorPeso);

}

bool ListaEhVazia(Caminho* caminho) {
    return caminho->cabeca == caminho->ultimo;
}


void ListaDestroiCaminho(Caminho** caminho) {
    Celula* aux = (*caminho)->cabeca, *aux1;
    while (aux != NULL) {
        aux1 = aux->prox;
        free(aux);
        aux = aux1;
    }
    free(*caminho);
    *caminho = NULL;
}


Caminho* ListaCria() {
    Caminho* lista = (Caminho*) malloc(1 * sizeof(Caminho));
    lista->cabeca = (Celula*) malloc(1 * sizeof(Celula));
    lista->cabeca->prox = NULL;
    lista->ultimo = lista->cabeca;
    return lista;
}

bool ListaRetiraFinal(Caminho* pLista) {
    if (ListaEhVazia(pLista))
        return false;
    Celula* aux = pLista->cabeca;
    while (aux->prox != pLista->ultimo)
        aux = aux->prox;
    pLista->ultimo = aux;
    free(aux->prox);
    aux->prox = NULL;
    return true;
}

bool ListaInsereFinalCaminho(Caminho* pLista, int x) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    if (nova == NULL)
        return false;
    nova->item = (Item*)malloc(sizeof(Item));  // Aloca memória para o novo item
    if (nova->item == NULL) {
        free(nova);  // Libera a célula se a alocação falhar
        return false;
    }
    nova->item->cidade = x;
    nova->prox = NULL;
    pLista->ultimo->prox = nova;
    pLista->ultimo = nova;
    return true;
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

void ListaLimpa(Caminho *lista) {
    Celula *aux = lista->cabeca->prox;  // Pula a célula cabeça da lista

    while (aux != NULL) {
        Celula *prox = aux->prox;  // Salva o próximo ponteiro antes de liberar a célula atual
        free(aux);  // Libera a célula atual
        aux = prox;  // Move para a próxima célula
    }

    // Atualiza o ponteiro de cabeça da lista para NULL e o último aponta para a cabeca, indicando uma lista vazia
    lista->cabeca->prox = NULL;
    lista->ultimo = lista->cabeca;
}


void ListaCopia(Caminho *lista1, Caminho *lista2) {
    Celula *aux = lista1->cabeca->prox; 

    // Limpa a lista de destino antes de copiar
    ListaLimpa(lista2);

    while (aux != NULL) {
        // Para cada elemento na lista original, insere no final da lista de destino
        ListaInsereFinalCaminho(lista2, aux->item->cidade);
        aux = aux->prox;
    }
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


bool ListaGet(Grafo *gp, int pos, Item *pX, int destino) {
    if(ListaTamanho(gp, pos) == 0)
        return false;
    Celula* aux = gp->cabeca[pos];
    aux = aux->prox;
    while(aux->item->cidade != destino && aux != NULL){
        aux = aux->prox;
    }    
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


void troca(Celula* cel1, Celula* cel2){
    Item aux = (*cel1->item);
    (*cel1->item) = (*cel2->item);
    (*cel2->item) = aux;
    
}


void encontraCaminho(Grafo *dados, int *visitadas, int passos, int cidadeAtual, Caminho *novoCaminho, int *melhorPeso, Caminho *melhorCaminho)
{

    static int melhorDistancia = INT_MAX;
    int distanciaTemp;

    // Adiciona a cidade atual ao novoCaminho
    ListaInsereFinalCaminho(novoCaminho, cidadeAtual);
    

    passos++;

    if (passos == dados->numCidades)
    {   
        Caminho *caminhoTemp;
        caminhoTemp = ListaCria();
        ListaCopia(novoCaminho, caminhoTemp);
        // Calcula a distancia total do caminho atual
        distanciaTemp = calculaCaminho(dados->numCidades, dados, caminhoTemp);
        
        if (distanciaTemp < melhorDistancia)
        {
            melhorDistancia = distanciaTemp;
            *melhorPeso = melhorDistancia;

            // Armazena o melhor caminho encontrado até o momento
            ListaCopia(caminhoTemp, melhorCaminho);
        }
        ListaDestroiCaminho(&caminhoTemp);
    }
    else
    {   
        // Atualiza a cidade atual como já visitada
        visitadas[cidadeAtual] = 1;
        for (int proximaCidade = 0; proximaCidade < dados->numCidades; proximaCidade++)
        {
            if (!visitadas[proximaCidade])
            {   
                // Recursivamente procura a próxima cidade
                encontraCaminho(dados, visitadas, passos, proximaCidade, novoCaminho, melhorPeso, melhorCaminho);
            }
        }
        // Atualiza novamente a cidade para não visitada
        visitadas[cidadeAtual] = 0;
    }

    // Remove a última cidade adicionada para manter o estado correto
    ListaRetiraFinal(novoCaminho);
}



int calculaCaminho(int qtd_cidades, Grafo *dados, Caminho *caminho)
{
    ListaInsereFinalCaminho(caminho, 0);
    Item distancias[qtd_cidades];
    int total = 0;
    int origem;
    int destino;
    int i = 0;
    
    Celula *aux = caminho->cabeca->prox;
    
    // Itera pelas Listas de adjacencias correspondentes e armazena as distancias num vetor de Itens
    while (aux != NULL && aux->prox != NULL) {
        origem = aux->item->cidade;
        destino = aux->prox->item->cidade;
        ListaGet(dados, origem, &distancias[i], destino);
        aux = aux->prox;
        i++;
    }
    

    //Calcula a distancia do caminho dado
    for (int i = 0; i < qtd_cidades; i++)
    {
        
        if(distancias[i].distancia == 0) 
            return 1000; //Valor de retorno utilizado para esta condicao nao entrar na verificacao

        total += distancias[i].distancia;
    }
    return total;
}
