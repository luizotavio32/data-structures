#include "stdio.h"
#include "stdlib.h"

// simulação de gerenciamento de memória de sistemas operacionais por meio de listas encadeadas
// cada segmento de memória é um "pedaço" do processo
// implementados inserção por best fit, next fit e first fit
// implementada remoção


struct SegmentoMemoria
{
        int livre;
        int idProcesso;
        struct SegmentoMemoria *prox;
};

struct ListaEncadeada
{
        int tamanho;
        struct SegmentoMemoria *primeiro;
        struct SegmentoMemoria *ultimo;
        struct SegmentoMemoria *nextFit;
};

struct SegmentoMemoria* cria_no()
{
        struct SegmentoMemoria *novo = malloc(sizeof(struct SegmentoMemoria));

        novo->livre = 1;
        novo->idProcesso = 0;
        novo->prox = NULL;

        return novo;
}

struct SegmentoMemoria* busca_processo(struct ListaEncadeada *lista, int idProcesso)
{
        struct SegmentoMemoria *temp = lista->primeiro;
        int i = 0;
        while(temp->prox != NULL){
                if(temp->idProcesso == idProcesso)
                        return temp;
                temp = temp->prox;
                i++;
    }
    return NULL;
}

void inicia_lista(struct ListaEncadeada *lista, int tam)
{
        lista->tamanho = tam;
        lista->primeiro = cria_no();
        lista->ultimo = lista->primeiro;

        int i;
        for (i = 1; i < tam; i++) {
                struct SegmentoMemoria *novo = cria_no();
                novo->prox = lista->primeiro;
                lista->primeiro = novo;
        }

        lista->nextFit = lista->primeiro;

}

void first_fit(struct ListaEncadeada *lista, int tamProcesso, int idProcesso)
{
        struct SegmentoMemoria *temp = lista->primeiro;
        struct SegmentoMemoria *segLivre = NULL;
        int processoInserido = 0;
        int tamLivre, i;

        //percorremos a lista até que ela acabe ou até o processo ser inserido na lista
        while(temp != NULL && processoInserido != 1) {
                tamLivre = 0;

                //encontramos um segmento livre
                if(temp->livre == 1){
                        segLivre = temp;

                        //a lista continua a ser percorrida, agora a partir do primeiro segmento livre encontrado,
                        //ela é percorrida até que se ache espaço suficiente para o processo novo
                        //ou até encontrar um segmento já preenchido com outro processo
                        while(segLivre != NULL && segLivre->livre == 1 && tamLivre != tamProcesso ){
                                segLivre = segLivre->prox;
                                tamLivre++;
                        }
                        if(tamLivre == tamProcesso){
                                int i;
                                for (i = 0; i < tamProcesso; i++) {
                                        temp->livre = 0;
                                        temp->idProcesso = idProcesso;
                                        temp = temp->prox;
                                }
                                printf("Processo inserido na memória com sucesso\n");
                                processoInserido = 1;
                                lista->nextFit = temp;
                                if(temp == NULL)
                                        lista->nextFit = lista->primeiro;

                        } else temp = segLivre;

                } else temp = temp->prox;
        }

        if(processoInserido  == 0) printf("Sem espaço na memória para inserção\n");
}

void best_fit(struct ListaEncadeada *lista, int tamProcesso, int idProcesso)
{
        struct SegmentoMemoria *temp = lista->primeiro;
        struct SegmentoMemoria *segLivre = NULL;
        struct SegmentoMemoria *bestFit = NULL;
        int processoInserido = 0;
        int tamLivre = 0;
        int melhorTam = lista->tamanho + 1;

        int i;
        while(temp != NULL && processoInserido != 1){
                tamLivre = 0;

                //encontramos um segmento livre
                if(temp->livre == 1){
                        segLivre = temp;

                        while(segLivre != NULL && segLivre->livre == 1){
                                segLivre = segLivre->prox;
                                tamLivre++;
                        }

                        if(tamLivre == tamProcesso){
                                int i;
                                for (i = 0; i < tamProcesso; i++) {
                                        temp->livre = 0;
                                        temp->idProcesso = idProcesso;
                                        temp = temp->prox;
                                }
                                printf("Processo inserido na memória com sucesso\n");
                                processoInserido = 1;
                                lista->nextFit = temp;
                                if(temp == NULL)
                                        lista->nextFit = lista->primeiro;
                        }
                        else {
                                if(tamLivre < melhorTam && tamLivre > tamProcesso){
                                        melhorTam = tamLivre;
                                        bestFit = temp;
                                }
                                temp = segLivre;
                        }
                } else temp = temp->prox;
        }

        if(processoInserido != 1 && melhorTam > tamProcesso){
                int i;
                temp = bestFit;
                for (i = 0; i < tamProcesso; i++) {
                        temp->livre = 0;
                        temp->idProcesso = idProcesso;
                        temp = temp->prox;
                }
                processoInserido = 1;
                lista->nextFit = temp;
                if(temp == NULL)
                        lista->nextFit = lista->primeiro;

        } else if (processoInserido != 1) printf("Sem espaço na memória para inserção\n");

}

void next_fit (struct ListaEncadeada *lista, int tamProcesso, int idProcesso)
{
        struct SegmentoMemoria *temp = lista->nextFit;
        struct SegmentoMemoria *segLivre = NULL;
        int processoInserido = 0;
        int tamLivre;

        //percorremos a lista até que ela acabe ou até o processo ser inserido na lista
        while(temp != NULL && processoInserido != 1 ) {
                tamLivre = 0;

                if(temp->livre == 1){
                        segLivre = temp;

                        while(segLivre != NULL && segLivre->livre == 1 && tamLivre != tamProcesso){
                                segLivre = segLivre->prox;
                                tamLivre++;

                        }
                        if(tamLivre == tamProcesso){
                                int i;
                                for (i = 0; i < tamProcesso; i++) {
                                        temp->livre = 0;
                                        temp->idProcesso = idProcesso;
                                        temp = temp->prox;
                                }
                                printf("Processo inserido na memória com sucesso\n");
                                processoInserido = 1;
                                lista->nextFit = temp;
                                if(temp == NULL)
                                        lista->nextFit = lista->primeiro;

                        } else temp = segLivre;

                } else temp = temp->prox;
        }

        if(processoInserido == 0 && lista->nextFit != lista->primeiro)
                first_fit(lista, tamProcesso, idProcesso);

}

void deleta_processo(struct ListaEncadeada *lista, int idProcesso)
{
        struct SegmentoMemoria *temp = busca_processo(lista, idProcesso);

        if(temp != NULL) {
                while(temp != NULL && temp->idProcesso == idProcesso){
                        temp->idProcesso = 0;
                        temp->livre = 1;
                        temp = temp->prox;
                }
        } else printf("Processo não existe na memória\n");
}

void imprime_lista(struct ListaEncadeada *lista)
{
        struct SegmentoMemoria *temp = lista->primeiro;
        int i;
        for (i = 0; i < lista->tamanho; i++) {
                printf("\t[%d]\n",temp->idProcesso);
                temp = temp->prox;
        }
}

int insere_processo(struct ListaEncadeada *lista)
{
        int idProcesso, tamanhoProcesso;

        printf("Tamanho:");
        scanf("%d", &tamanhoProcesso);
        printf("\nId:");
        scanf("%d", &idProcesso);

        if(busca_processo(lista, idProcesso) != NULL){
                printf("Processo já existe na mémoria\n");
                return 0;

        } else {
                int op;
                printf("1- First Fit\n2- Best Fit\n3- Next Fit\n");
                scanf("%d", &op);
                if(op == 1) first_fit(lista, tamanhoProcesso, idProcesso);
                else if(op == 2) best_fit(lista, tamanhoProcesso, idProcesso);
                else if(op == 3) next_fit(lista, tamanhoProcesso, idProcesso);
        }
}

int main(int argc, char const *argv[])
{
        int tam;
        struct ListaEncadeada lista;
        printf("Tamanho da memória:\n");
        scanf("%d", &tam);
        inicia_lista(&lista, tam);

        int op = 0;
        while(op != 4){
                printf("1- Insere processo.\n2- Deleta processo.\n3- Imprime memória.\n4- Finaliza\n");
                scanf("%d", &op);
                if(op == 1) insere_processo(&lista);
                else if(op == 2){
                        int id;
                        printf("Insira o id do processo:\n");
                        scanf("%d", &id);
                        deleta_processo(&lista, id);
                } else if(op == 3) imprime_lista(&lista);
                printf("\n\n\n\n");
        }

        return 0;
}
