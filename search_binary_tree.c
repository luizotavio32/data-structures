#include <stdio.h>
#include <stdlib.h>

struct node
{
        int key;
        struct node* left;
        struct node* right;
        struct node* dad;
};

struct tree
{
        struct node* root;
        int height;
        int nodeNumbers;
};


void start_tree(struct tree *tree)
{
        tree->root = NULL;
        tree->height = 0;
        tree->nodeNumbers = 0;
}

struct node* create_node()
{
        struct node *node = malloc(sizeof(struct node));

        scanf("%d", &node->key);
        node->right = NULL;
        node->left = NULL;
        node->dad = NULL;

        return node;
}

struct node* find_node(struct node *node, int key)
{
        if(key == node->key || node == NULL) // (achou o nó || nó não existe)
                return node;
        else if(key < node->key)
                return find_node(node->left, key);
        else return find_node(node->right, key);
}

struct node* find_min(struct node *node)
{
        while (node->left != NULL)
                node = node->left;

        return node;
}
 
struct node* find_max(struct node *node)
{
        while (node->right != NULL)
                node = node->right;

        return node;
}


void binaryTree_insertion(struct tree *tree)
{
        struct node *temp = tree->root;
        struct node *dad = NULL;
        struct node *newNode = create_node();

        while(temp != NULL){
                dad = temp; // como temp muda a cada iteração precisamos saber quem ele era antes pois futuramente será nó pai
                if(newNode->key < temp->key){
                        temp = temp->left;
                } else temp = temp->right;

                newNode->dad = dad;
        }

        if(dad == NULL)
                tree->root = newNode; // dad permaneceu NULL logo a arvore estava vazia (sequer entrou no laço while)
        else if (newNode->key < dad->key) 
                dad->left = newNode;
        else dad->right = newNode;
}

void transplant(struct tree *tree, struct node *node1, struct node *node2)
{
        if(node1->dad == NULL)
                tree->root = node2;
        else if (node1 == node1->dad->left)
                node1->dad->left = node2;
        else node1->dad->right = node2;

        if(node2 != NULL)
                node2->dad = node1->dad;
}

void binaryTree_removal(struct tree *tree, struct node *node)
{

        if(node->left == NULL && node->right == NULL) { // caso o nó a ser removido seja uma folha
                if(node->dad->left == node)
                        node->dad->left == NULL;     
                else  node->dad->right = NULL; 
        } else {
                if(node->left == NULL)
                        transplant(tree,node,node->right);
                else if(node->right == NULL) 
                        transplant(tree, node, node->left);     
                else {
                        struct node *minNode = find_min(node->right);
                        if(minNode->dad != node){
                                transplant(tree, minNode, minNode->right);
                                minNode->right = node->right;
                                minNode->right->dad = minNode;
                        }
                        transplant(tree, node, minNode);
                        minNode->left = node->left;
                        minNode->left->dad = minNode;
                }

        } 
        free(node);
}

int main(void)
{
        
}