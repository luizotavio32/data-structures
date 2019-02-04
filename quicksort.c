#include <stdio.h>
#include <stdlib.h>
#define TAM_NOME 15
 
typedef struct{
        int idade;
        int ordem; // futuramente será usado para testar a estabilidade
        char nome[TAM_NOME];
}TipoPessoa;
 
 
void troca(TipoPessoa *a, TipoPessoa *b)
{
        TipoPessoa *temp = malloc(sizeof(TipoPessoa));
        *temp = *a;
        *a = *b;
        *b = *temp;
        free(temp);
}
 
int particao(TipoPessoa *array, int menor, int maior)
{
        int pivot = array[maior].idade;
        int i = (menor - 1);
        int j;
 
        for (j = menor; j < maior; j++) {
                if(array[j].idade <= pivot){
                        i++;
                        /*TipoPessoa temp;
                        temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;*/
 
 
 
                        troca(&array[i], &array[j]);
 
                }
        }
       /* TipoPessoa temp2;
        temp2 = array[i + 1];
        array[i + 1] = array[maior];
        array[maior] = temp2; */
 
 
        troca(&array[i + 1], &array[maior]);
        return i + 1;
}
 
void quick_sort(TipoPessoa *array, int menor, int maior) {
        if(menor < maior){
                int particionador = particao(array, menor, maior);
                quick_sort(array, menor, particionador - 1);
                quick_sort(array, particionador + 1, maior);
 
        }
}
 
 
 
int main(void)
{
        int numPessoas;
        TipoPessoa *listaPessoas;
        scanf("%d", &numPessoas);
        listaPessoas = malloc(numPessoas * sizeof(TipoPessoa));
 
        int i;
        for(i = 0; i < numPessoas; i++){
                scanf("%s", listaPessoas[i].nome);
                scanf("%d", &listaPessoas[i].idade);
                listaPessoas[i].ordem = i;
        }
 
        quick_sort(listaPessoas, 0, numPessoas - 1);
 
        int primeiroNome, proximosImprimir;
        scanf("%d %d", &primeiroNome, &proximosImprimir);
 
        int estavel = 1;
        for(i = 1; i < numPessoas; i++){
                if(listaPessoas[i - 1].idade == listaPessoas[i].idade){
                        if(listaPessoas[i - 1].ordem > listaPessoas[i].ordem){
                                estavel = 0;
                                break;
                        }
                }
        }
 
        if(estavel == 0)
                printf("no\n");
        else
                printf("yes\n");
 
        for(i = primeiroNome - 1; i  < primeiroNome + proximosImprimir - 1; i++){
                printf("%s %d\n", listaPessoas[i].nome, listaPessoas[i].idade);
        }
 
        free(listaPessoas);
}