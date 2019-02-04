#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOME_SIZE 15
 
struct node
{
        int *ano;
        char nome[NOME_SIZE];
        struct node *left;
        struct node *right;
        struct node *dad;
        int nodeHeight;
        int balanceFactor;
        int anoCount;
};
 
struct tree
{
        struct node *root;
        //int nodeNumbers, height;
};
 
char *strlwr(char *str)
{
        unsigned char *p = (unsigned char *)str;
 
        while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
        }
 
        return str;
}
 
int minInt(int a, int b)
{
        if(a >= b)
                return b;
        else
                return a;
}
 
 
int maxInt(int a, int b)
{
        if(a >= b)
                return a;
        else
                return b;
}
 
int compare_strings(char *a , char *b)
{
     int i;
     char c[NOME_SIZE];
     char d[NOME_SIZE];
     strcpy(c,a);
     strcpy(d,b);
 
     // passando as strings para minúsculas teremos valores ascii uniformes
     strlwr(c);
     strlwr(d);
 
     // vamos comparar duas strings por meio de seu valor ascii dessa forma saberemos qual vem primeiro na ordem alfabética
 
     if(strlen(a) > strlen(b)){
                for(i = 0; i < strlen(b); i++){
                        if(c[i] < d[i])
                                return 0;
                        else if (c[i] > d[i])
                                return 1;
                        }
                return 1; // caso as strings sejam iguais até certo ponto, porém a primeira é maior, logo vem depois na ordenção alfabética
        } else {
                for(i = 0; i < strlen(a); i++){
                        if(c[i] < d[i])
                                return 0;
                        else if (c[i] > d[i])
                                return 1;
                        }
                return 0;
        }
}
 
void start_tree(struct tree *tree)
{
        tree->root = NULL;
}
 
struct node* create_node(char *nome, int ano)
{
        struct node *node = malloc(sizeof(struct node));
        node->right = NULL;
        node->left = NULL;
        node->dad = NULL;
        strcpy(node->nome, nome);
        node->anoCount = 1;
        node->ano = malloc(sizeof(int));
        node->ano[0] = ano;
 
        return node;
}
 
struct node* find_node(struct node *node, char *nome)
{
        if(node == NULL)  //nó não existe
                return NULL;
        else if(strcmp(nome,node->nome) == 0) // achou o nó
                return node;
        else if(compare_strings(nome, node->nome) == 0)
                return find_node(node->left, nome); // busca na sub arv esquerda
        else return find_node(node->right, nome); //busca na sub arv direita
}
 
void fix_height(struct node *node)
{
        while(node != NULL){
                if(node->left == NULL && node->right == NULL){
                        node->nodeHeight = 1;
                        node->balanceFactor = 0;
 
                }
                else if(node->right == NULL && node->left != NULL){
                        node->nodeHeight = node->left->nodeHeight + 1;
                        node->balanceFactor = node->left->nodeHeight;
                }
                else if(node->right != NULL && node->left == NULL){
                        node->nodeHeight = node->right->nodeHeight + 1;
                        node->balanceFactor =  -1*(node->right->nodeHeight);
                }
                else {
                        node->nodeHeight = maxInt(node->left->nodeHeight, node->right->nodeHeight) + 1;
                        node->balanceFactor = node->left->nodeHeight - node->right->nodeHeight;
                }
                node = node->dad;
        }
}
 
void rotate_left(struct tree *tree, struct node *node)
{
        struct node *temp = node->right;
        node->right = temp->left;
 
        if(temp->left != NULL)
                temp->left->dad = node;
        temp->dad = node->dad;
 
        if(node->dad == NULL)
                tree->root = temp;
        else if (node == node->dad->left)
                node->dad->left = temp;
        else
                node->dad->right = temp;
 
        temp->left = node;
        node->dad = temp;
}
 
void rotate_right(struct tree *tree, struct node *node)
{
        struct node *temp = node->left;
        node->left = temp->right;
 
        if(temp->right != NULL)
                temp->right->dad = node;
        temp->dad = node->dad;
 
        if(node->dad == NULL)
                tree->root = temp;
        else if(node == node->dad->left)
                node->dad->left = temp;
        else
                node->dad->right = temp;
 
        temp->right = node;
        node->dad = temp;
}
 
void rebalance(struct tree *tree, struct node *node)
{
        struct node *temp = node->dad;
        while(temp != NULL){
                if(temp->balanceFactor == -2 && temp->right->balanceFactor == -1){ //caso 1
                        //printf("\ncaso1\n");
                        rotate_left(tree, temp);
                        fix_height(temp);
                }
                else if(temp->balanceFactor == -2 && temp->right->balanceFactor == 1){ //caso 2
                        //printf("\ncaso2\n");
                        rotate_right(tree, temp->right);
                        fix_height(temp->right->right);
                        rotate_left(tree, temp);
                        fix_height(temp);
                }
                else if (temp->balanceFactor == 2 && temp->left->balanceFactor == 1){ //caso 3
                        //printf("\ncaso3\n");
                        rotate_right(tree, temp);
                        fix_height(temp);
                }
                else if (temp->balanceFactor == 2 && temp->left->balanceFactor == -1){ //caso 4
                        //printf("\ncaso4\n");
                        rotate_left(tree, temp->left);
                        fix_height(temp->left->left);
                        rotate_right(tree, temp);
                        fix_height(temp);
                }
                temp = temp->dad;
        }
}
 
 
void AVLTree_insertion(struct tree *tree, char *nome, int ano)
{
        struct node *temp = tree->root;
        struct node *dad = NULL;
        struct node *newNode = create_node(nome, ano);
 
        while(temp != NULL){
                dad = temp; // como temp muda a cada iteração precisamos saber quem ele era antes pois futuramente será nó pai
                if(compare_strings(newNode->nome, temp->nome) == 0){
                        temp = temp->left;
                } else temp = temp->right;
 
                newNode->dad = dad;
        }
 
        if(dad == NULL)
                tree->root = newNode; // dad permaneceu NULL logo a arvore estava vazia (sequer entrou no laço while)
        else if (compare_strings(newNode->nome, newNode->dad->nome) == 0)
                dad->left = newNode;
        else dad->right = newNode;
 
        fix_height(newNode);
        rebalance(tree, newNode);
}
 
void add_ano (struct node *node, int ano)
{
        node->anoCount = node->anoCount + 1;
        node->ano = realloc(node->ano, sizeof(int) * node->anoCount);
        node->ano[node->anoCount - 1] = ano;
}
 
 
 
 
 
 
 
int main(int argc, char const *argv[])
{
        int operacao = 3;
        int ano;
        char nome [NOME_SIZE];
 
        struct tree tree;
        start_tree(&tree);
 
 
        while(operacao != 0){
                scanf("%d", &operacao);
                if(operacao == 1){
                        scanf("%s", nome);
                        scanf("%d", &ano);
                        struct node *temp = find_node(tree.root, nome);
                        if(temp == NULL){
                                AVLTree_insertion(&tree, nome, ano);
                        } else{
                                add_ano(temp, ano);
                        }
 
                } else if (operacao == 2){
                        scanf("%s", nome);
                        struct node *temp = find_node(tree.root, nome);
                        if(temp == NULL){
                                printf("\n0");
                        } else {
                                printf("\n%d ", temp->nodeHeight);
                                int i;
                                for(i = 0; i < temp->anoCount; i++)
                                        printf("%d ",temp->ano[i]);
                             }
                        }
                }
 
 
}