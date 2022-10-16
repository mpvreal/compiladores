#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "ternarytree.h"

typedef struct node node_t;
typedef struct tree tree_t;

// Nó da árvore ternária.
struct node{

    struct key{

        double x,
               y;
    } key;

    void* object;

    node_t* parent,
          * left,
          * upper,
          * lower;
};

// Árvore ternária.
struct tree{

    size_t size;

    node_t* root;
};

static inline node_t* node_new(double x, double y, void* object){

    node_t* node = (node_t*) malloc(sizeof(node_t));

    node->object = object;

    node->parent = NULL;
    node->left = NULL;
    node->upper = NULL;
    node->lower = NULL;

    node->key.x = x;
    node->key.y = y;

    return node;
}

static size_t levelorder_traversal(node_t* node, node_t** array, size_t n);

static void util_tree_print(node_t* node, printfn_t object_print);

/*****************************************************************/

void* tree_new(){

    tree_t* tree = (tree_t*) malloc(sizeof(tree_t));

    if(tree != NULL){       // Se a árvore foi alocada com sucesso

        tree->size = 0;
        tree->root = NULL;
    }

    return tree;
}

void tree_insert(void* tree, double x, double y, void* object){

    // Verifica se a árvore foi criada.
    assert(tree != NULL);

    tree_t* t = (tree_t*) tree;

    // Buffer para percorrer a árvore.
    node_t** buffer = &t->root,             
           * new_node = node_new(x, y, object); // Novo nó.

    // Primeiro, encontramos uma referência ao ponteiro que
    // apontará para o novo nó...

    // Enquanto buffer não se referir a um ponteiro nulo...
    while(*buffer){

        // Atualizamos o pai do novo nó.
        new_node->parent = *buffer;

        // Se x for menor que o x do nó atual... 
        if(x < (*buffer)->key.x){      

            // Buffer recebe uma referência ao ponteiro que aponta 
            // para o filho esquerdo do nó atual.
            buffer = &(*buffer)->left;

        } else{ // Se não...
            // Se y for menor que o y do nó atual...
            if(y < (*buffer)->key.y){       

                // Buffer recebe uma referência ao ponteiro que 
                // aponta para o filho inferior do nó atual.
                buffer = &(*buffer)->lower;

            } else{ // Se não...

                // Buffer recebe uma referência ao ponteiro que
                // aponta para o filho superior do nó atual.
                buffer = &(*buffer)->upper; 
            }
        }
    }

    // Tendo a referência, podemos alterar o conteúdo desse
    // ponteiro e fazemos ele apontar para o novo nó.
    *buffer = new_node;

    ++t->size;
}

void tree_print(void* tree, printfn_t object_print){

    assert(tree != NULL);

    tree_t* t = (tree_t*) tree;

    util_tree_print(t->root, object_print);
}

/******************************************************************************/

// static inline node_t* node_new(double x, double y, void* object){

//     node_t* node = (node_t*) malloc(sizeof(node_t));

//     node->object = object;

//     node->parent = NULL;
//     node->left = NULL;
//     node->upper = NULL;
//     node->lower = NULL;

//     node->key.x = x;
//     node->key.y = y;

//     return node;
// }

static size_t levelorder_traversal(node_t* node, node_t** array, size_t n){

    if(node == NULL)
          return n;

     array[n++] = node;

    if(node->left != NULL)
        n = levelorder_traversal(node->left, array, n);
    if(node->lower != NULL)
        n = levelorder_traversal(node->lower, array, n);
    if(node->upper != NULL)
        n = levelorder_traversal(node->upper, array, n);

     return n;
}

static void util_tree_print(node_t* node, printfn_t object_print){

    if(node == NULL) 
        return;

    printf("(%lf, %lf)", node->key.x, node->key.y);
    
    if(object_print != NULL){

        printf(": ");
        object_print(node->object);
    }
    if(node->left){
        printf("Left: (%lf, %lf)", node->left->key.x, node->left->key.y);

        if(object_print != NULL){

            printf(": ");
            object_print(node->left->object);
        }
    }

    if(node->lower){
        printf("Lower: (%lf, %lf)", node->lower->key.x, node->lower->key.y);

        if(object_print != NULL){

            printf(": ");
            object_print(node->lower->object);
        }
    }

    if(node->upper){
        printf("Upper: (%lf, %lf)", node->upper->key.x, node->upper->key.y);

        if(object_print != NULL){

            printf(": ");
            object_print(node->upper->object);
        }
    }

    putchar('\n');

    util_tree_print(node->left, object_print);

    util_tree_print(node->lower, object_print);

    util_tree_print(node->upper, object_print);
}