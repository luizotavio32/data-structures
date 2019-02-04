#include <stdio.h>
#include <stdlib.h>

struct no
{
       struct no* prox;
       int indiceVertice;
};

struct tipoGrafo
{
        int vertices;
        struct no**listaAdj;
};

void inicia_grafo(struct tipoGrafo *grafo, int n)
{
        grafo->vertices = n;
        grafo->listaAdj = malloc (sizeof(struct no*) * n);
        int i;
        for(i = 0; i < n ;i++)
                grafo->listaAdj[i] = NULL;
}

struct no* cria_no(int indiceVertice)
{
      struct no *novoNo = malloc (sizeof(struct no));
      novoNo->indiceVertice = indiceVertice;
      return novoNo;
}

void insere_no_grafo(struct tipoGrafo *grafo, int amigo1, int amigo2)
{
        struct no *no1 = cria_no(amigo1);
        struct no *no2 = cria_no(amigo2);

        no2->prox = grafo->listaAdj[amigo1];
        grafo->listaAdj[amigo1] = no2;
        no1->prox = grafo->listaAdj[amigo2];
        grafo->listaAdj[amigo2] = no1;
        
}

int fila_vazia(int inicio, int fim)
{
        if(inicio >= fim)
                return 1;
        else
                return 0;
}

int verifica_adjacencia(struct tipoGrafo *grafo, int u, int *v, int *verticesProcessados)
{
        struct no *temp = grafo->listaAdj[u];
        while(temp != NULL){
                if(verticesProcessados[temp->indiceVertice] == 0){
                        *v = temp->indiceVertice;
                        return 1;
                }
        temp = temp->prox;
        }
        return 0;
}




void investiga_grau (struct tipoGrafo *grafo, int amigo1, int amigo2)
{
        int *verticesProcessados = malloc(grafo->vertices * sizeof(int));
        int *nivel = malloc(grafo->vertices * sizeof(int));
        //int *predecessor = malloc(grafo->vertices * sizeof(int));
        int *fila = malloc(grafo->vertices * sizeof(int));
        int inicio = 0;
        int fim = 0;
        int i;
        for(i = 0; i < grafo->vertices; i++){
                nivel[i] = -1;
                verticesProcessados[i] = 0;
        }

        verticesProcessados[amigo1] = 1;
        fila[fim] = amigo1;
        fim++;
        nivel[amigo1] = 0;
        int u, v;
        while (!fila_vazia(inicio,fim) && nivel[amigo2] == -1){ // para nivel[amigo2] != -1, ja saberemos o grau de separação entre os dois vértices
                u = fila[inicio];
                while(verifica_adjacencia(grafo, u, &v, verticesProcessados) && nivel[amigo2] == -1){
                        if(verticesProcessados[v] == 0){
                                verticesProcessados[v] = 1;
                                fila[fim] = v;
                                nivel[v] = nivel[u] + 1;
                                // predecessor[v] = u;
                                fim++;
                        }
                }
                inicio++;
        }

        if(nivel[amigo2] != -1)
                printf("%d\n", nivel[amigo2]);
        else
                printf("Impossible\n");    
}

int main(void)
{
        int pessoas, relacoes, i, amigo1, amigo2;
        struct tipoGrafo grafo;

        scanf("%d", &pessoas);
        scanf("%d", &relacoes);
        inicia_grafo(&grafo, pessoas);
        
        for(i = 0; i < relacoes; i++){
                scanf("%d %d", &amigo1, &amigo2);
                insere_no_grafo(&grafo, amigo1, amigo2);
        }

        scanf("%d", &relacoes);
        for(i = 0; i < relacoes; i++){
                scanf("%d %d", &amigo1, &amigo2);
                investiga_grau(&grafo, amigo1, amigo2);
        }

}
