#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


void tree_insert(Tree_Node** root, char data){
    //TODO
    //create node
    Tree_Node* z = (Tree_Node*)malloc(sizeof(Tree_Node));
    z->data = data;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;

    //Find the right parent
    Tree_Node* x = (*root);
    Tree_Node* y = NULL;
    while (x != NULL)
    {
        y = x;
        if (z->data < y->data){x = x->left;}
        else {x = x->right;}
    }
    z->parent = y;

    //Find the correct position of z relative to y (its parent)
    if (y == NULL){(*root) = z;} //Tree was NULL
    else
    {
        if (z->data < y->data){y->left = z;}
        else {y->right = z;}
    }
}

Tree_Node* create_bst (char data[]){
    Tree_Node* root = NULL;
    int i = 0;
    while (data[i] != '\0')
    {
        tree_insert(&root, data[i]);
        i++;
    }
    return root;
}

Tree_Node* tree_search(Tree_Node* root, char data){
    //TODO
    if (root == NULL || root->data == data)
    {
        return root;
    }
    if (data < root->data){return tree_search(root->left, data);}
    else{return tree_search(root->right, data);}
}

void tree_print_sorted(Tree_Node* root){
    //perform In-Order traversal of BST
    if (root != NULL)
    {
        tree_print_sorted(root->left);
        printf("%c", root->data);
        tree_print_sorted(root->right);
    }
    // printf("\n");
}

void tree_delete(Tree_Node* root){
    //TODO
    //perform post-order traversal of BST
    if (root == NULL)
    {
        return;
    }
    //recursively delete the children first
    tree_delete(root->left);
    tree_delete(root->right);

    //free the root
    free(root);
}


