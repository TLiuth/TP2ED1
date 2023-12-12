#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"


Grafo *alocarGrafo(int qtd_cidades)
{
    Grafo *gp = malloc(sizeof(Grafo)); //Aloca memoria para a estrutura do grafo
    gp->numCidades = qtd_cidades;

    gp->cabeca = malloc(qtd_cidades * sizeof(Celula*)); //Aloca um vetor de ponteiros para listas encadeadas
    gp->ultimo = malloc(qtd_cidades * sizeof(Celula*)); //Aloca um vetor de ponteiros para os ultimos elementos das listas encadeadas

    for(int i = 0; i < qtd_cidades; i++){
        gp->cabeca[i] = malloc(sizeof(Celula)); // aloca memoria para uma unica celula, que sera a cabeca da lista propriamente dita
        gp->ultimo[i] = gp->cabeca[i]; // o ponteiro de ultimo aponta para o mesmo endereço que o ponteiro da cabeca (nao ha elementos na lista ainda)
        gp->cabeca[i]->tam = 0; // inicia o tamanho da lista como zero
        gp->cabeca[i]->prox = NULL; // o proximo da celula cabeca eh NULL
        gp->cabeca[i]->item = NULL; // Nao ha itens
        //O objetivo de inicializar a cabeca eh armazenar o tamanho das listas
        //As demais celulas terao o campo tam, mas esse nao sera utilzado
    }
    
    return gp;
}

void imprimeCaminho(Caminho* caminho, int *melhorPeso) {
    
    printf("Melhor caminho : ");
    Celula* aux = caminho->cabeca->prox;
    // Percorre a lista encadeada
    while (aux != NULL) {
        printf("%d ", aux->item->cidade);
        aux = aux->prox; // Move para a proxima celula
    }
    printf("\nMelhor distancia : %d\n", *melhorPeso);

}

bool ListaEhVazia(Caminho* caminho) {
    return caminho->cabeca == caminho->ultimo; // Verifica se a cabeca aponta para o ultimo
}

void ListaDestroiCaminho(Caminho** caminho) {
    Celula* aux = (*caminho)->cabeca, *aux1;
    // Percorre a lista encadeada
    while (aux != NULL) {
        aux1 = aux->prox;
        free(aux); // Libera a memoria para a celula atual
        aux = aux1; // Move para a proxima celula
    }
    free(*caminho); // Libera a memoria para alocada para a estrutura 
    *caminho = NULL;
}


Caminho* ListaCria() {
    // Aloca memoria para a estrutura
    Caminho* lista = (Caminho*) malloc(1 * sizeof(Caminho));

    // Aloca memoria para a celula cabeca da lista
    lista->cabeca = (Celula*) malloc(1 * sizeof(Celula));

    lista->cabeca->prox = NULL;
    lista->ultimo = lista->cabeca;
    return lista;
}

bool ListaRetiraFinal(Caminho* pLista) {
    // Verifica se a lista esta vazia
    if (ListaEhVazia(pLista))
        return false;

    Celula* aux = pLista->cabeca;
    
    // Percorre a lista ate encontrar o ultimo elemento
    while (aux->prox != pLista->ultimo)
        aux = aux->prox;
    pLista->ultimo = aux; // Atualiza o 'ultimo' para o penultimo elemento
    free(aux->prox); // Libera a memoria alocada para o ultimo elemento
    aux->prox = NULL; // Define o ponteiro 'prox' do penultimo elemento como NULL, representando o final
    return true;
}

bool ListaInsereFinalCaminho(Caminho* pLista, int x) {
    // Aloca memoria para uma nova celula
    Celula* nova = (Celula*) malloc(sizeof(Celula));

    if (nova == NULL)
        return false;
    
    nova->item = (Item*)malloc(sizeof(Item));  // Aloca memória para o novo item
    
    if (nova->item == NULL) {
        free(nova);  // Libera a célula se a alocação falhar
        return false;
    }
    nova->item->cidade = x; // Define o valor da cidade como o novo item
    nova->prox = NULL; // Configura o ponteiro 'prox' da nova celula como NULL, pois ela é a ultima na lista
    pLista->ultimo->prox = nova; // Atualiza o ponteiro 'prox' do antigo ultimo elemento
    pLista->ultimo = nova; // Atualiza o ponteiro 'ultimo' para a nova celula
    return true;
}


bool ListaInsereFinal(Grafo *gp, Item x, int pos) {
    // Aloca memoria para uma nova celula
    Celula* nova = malloc(sizeof(Celula));

    nova->item = malloc(sizeof(Item)); // Aloca memoria para o novo item
    
    if (nova == NULL)
        return false;    
    
    *(nova->item) = x; // Define o valor do item como o novo item
    nova->prox = NULL; // Define o ponteiro 'prox' da nova celula como NULL, indicando o final

    
    gp->ultimo[pos]->prox = nova; // Atualiza o ponteiro 'prox' do ultimo para apontar para a nova celula
    gp->ultimo[pos] = nova; // Atualiza o ponteiro 'ultimo' para a nova celula

    (*gp->cabeca[pos]).tam++;

    return true;
}

void ListaLimpa(Caminho *lista) {
    Celula *aux = lista->cabeca->prox;  

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

    // Percorre a lista encadeada
    while (aux != NULL) {
        // Para cada elemento na lista original, insere no final da lista de destino
        ListaInsereFinalCaminho(lista2, aux->item->cidade);
        aux = aux->prox;
    }
}



void desalocarGrafo(Grafo **dados)
{
    // Percorre todas as listas encadeadas no grafo e as desaloca
    for(int i = 0; i < (*dados)->numCidades; i++){
            ListaDestroi(&((*dados)->cabeca[i]));;
    }
    free((*dados)->cabeca); // Libera a memoria alocada para o vetor de ponteiros para a 'cabeca'
    free((*dados)->ultimo); // Libera a memoria alocada para o vetor de ponteiros para o 'ultimo'
    free(*dados); // Libera a memoria alocada para o grafo
    *dados = NULL;

}

void ListaDestroi(Celula** celula) {
    Celula* aux = *celula;
    Celula *aux1;

    // Percorre a lista encadeada
    while (aux != NULL) {
        aux1 = aux->prox;
        if (aux->item != NULL) {
            free(aux->item); // Libera a memoria para o item se ele nao for nulo
        }
        free(aux); // Libera a memoria para a celula atual
        aux = aux1; // Move para a proxima celula
    }
    *celula = NULL;
}


void leGrafo(Grafo **dados)
{
    int origem;
    Item aux;

    // Loop para percorrer as cidades de origem
    for(int i = 0; i < (*dados)->numCidades; i++){
        // Loop para percorrer as cidades de destino
        for(int j = 0; j < (*dados)->numCidades; j++){
            scanf("%d%d%d", &origem, &aux.cidade, &aux.distancia);
            ListaInsereFinal(*dados, aux, origem); // Insere as informações nas listas
            
        }
    }
}


bool ListaGet(Grafo *gp, int pos, Item *pX, int destino) {
    if(ListaTamanho(gp,pos) == 0)
        return false;
    
    // Inicializa um ponteiro auxiliar para o inicio da lista
    Celula* aux = gp->cabeca[pos]->prox;

    // Percorre a lista ate encontrar o destino desejado ou chegar ao final da lista
    while(aux->item->cidade != destino && aux != NULL){
        aux = aux->prox;
    }    
    if (aux->item != NULL){
        (*pX) = *(aux->item); // Copia o conteudo do item para o ponteiro pX
    }
    
    return true;
}


void imprimeOrdenado(Grafo *dados)
{
    Item aux;
    Celula *p; // Ponteiro para percorrer a lista
    for(int i = 0; i < (dados)->numCidades; i++){
        p = dados->cabeca[i]->prox; // Aponta para o primeiro elemento da lista correspondente
        printf("Adjacencias do vertice %d: ", i);
        // Percorre a lista ate o final
        while (p != NULL) { 
            aux = *(p->item); // Obtem o item
            printf("(%d ,%d) -> ", aux.cidade, aux.distancia);
            p = p->prox; // Move para a proxima celula
        }
        printf("NULL\n"); 
    }
}

int ListaTamanho(Grafo* gp, int index) {
    return gp->cabeca[index]->tam;
}

void ordenaGrafo(Grafo* dados){
    // Percorre todas as cidades no grafo
    for(int i = 0; i < dados->numCidades; i++){
        // Chama a funcao para ordenar a respectiva lista
        ordenaLista(&(dados->cabeca[i]));
    }
}

void ordenaLista(Celula** head) {
    // Verifica se a lista esta vazia ou se possui so um elemento
    if (*head == NULL || (*head)->prox == NULL) {
        return;
    }

    Celula *aux = (*head)->prox; // Inicializa um ponteiro auxiliar para o inicio da lista
    Celula *aux1;

    // Percorre a lista utilizando o algoritmo de ordenacao 'BubbleSort'
    while (aux != NULL) {
        aux1 = aux->prox;  
        while(aux1 != NULL){
            // Compara as distancias entre os elementos
            if(aux->item->distancia > aux1->item->distancia){
                troca(aux, aux1); // Troca se necessario
            }else if(aux->item->distancia == aux1->item->distancia){
                // Se as distancias forem iguais, compara as cidades
                if(aux->item->cidade > aux1->item->cidade){
                troca(aux, aux1); // Troca se necessario
                }
            }
            aux1 = aux1->prox;
        }
        aux = aux->prox;
    }
}

void troca(Celula* cel1, Celula* cel2){
    // Copia o conteudo da primeira celula para uma variavel auxiliar
    Item aux = (*cel1->item);
    // Copia o conteudo da segunda celula para a primeira
    (*cel1->item) = (*cel2->item);
    // Copia o conteudo da variavel auxiliar para segunda celula
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
        // Cria uma lista Caminho temporaria
        Caminho *caminhoTemp; 
        caminhoTemp = ListaCria();
        // Copia a lista 'novoCaminho' para essa temporaria
        ListaCopia(novoCaminho, caminhoTemp);

        // Calcula a distancia total do caminho atual
        distanciaTemp = calculaCaminho(dados->numCidades, dados, caminhoTemp);
        
        if (distanciaTemp < melhorDistancia)
        {
            melhorDistancia = distanciaTemp;
            *melhorPeso = melhorDistancia;

            // Armazena o melhor caminho encontrado ate o momento
            ListaCopia(caminhoTemp, melhorCaminho);
        }
        // Libera a memoria da lista temporaria
        ListaDestroiCaminho(&caminhoTemp);
    }
    else
    {   
        // Atualiza a cidade atual como ja visitada
        visitadas[cidadeAtual] = 1;
        for (int proximaCidade = 0; proximaCidade < dados->numCidades; proximaCidade++)
        {
            if (!visitadas[proximaCidade])
            {   
                // Recursivamente procura a proxima cidade
                encontraCaminho(dados, visitadas, passos, proximaCidade, novoCaminho, melhorPeso, melhorCaminho);
            }
        }
        // Atualiza novamente a cidade para nao visitada
        visitadas[cidadeAtual] = 0;
    }

    // Remove a ultima cidade adicionada para manter o estado correto
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
    
    // Itera pelas listas de adjacencias correspondentes e armazena as distancias num vetor de Itens
    while (aux != NULL && aux->prox != NULL) {
        origem = aux->item->cidade;
        destino = aux->prox->item->cidade;
        ListaGet(dados, origem, &distancias[i], destino); // Obtem a distancia correspondente de uma cidade a outra e armazena no vetor
        aux = aux->prox; // Move para a proxima celula
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
