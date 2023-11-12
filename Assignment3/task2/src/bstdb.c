#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

typedef struct TreeNode
{
    int doc_id;
    char* name;
    int word_count;
    char* author;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
}TreeNode;

TreeNode* root = NULL;
int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	return 1;
}

TreeNode* insert(TreeNode** root, char *name, int word_count, char *author)
{
    TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));
    new->word_count = word_count;
    new->name = (char*)malloc(sizeof(char) * 30);
    new->author = (char*)malloc(sizeof(char) * 30);
    new->left = NULL;
    new->right = NULL;
    strcpy(new->name, name);
    strcpy(new->author, author);
    srand(time(NULL) + word_count);
    new->doc_id = rand() % RAND_MAX;
    
    TreeNode* x = (*root);
    TreeNode* y = NULL;
    while (x != NULL)
    {
        y = x;
        if (new->doc_id < y->doc_id){x = x->left;}
        else {x = x->right;}
    }
    new->parent = y;
    
    if (y == NULL){(*root) = new;}
    else
    {
        if (new->doc_id < y->doc_id){y->left = new;}
        else{y->right = new;}
    }
    return new;
}
int
bstdb_add ( char *name, int word_count, char *author ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name, word_count and author of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
    TreeNode* new = insert(&root, name, word_count, author);
    return new->doc_id;
	return -1;
}
TreeNode* search(TreeNode* root, int doc_id)
{
    if (root == NULL || root->doc_id == doc_id)
    {
        return root;
    }
    if (doc_id < root->doc_id){return search(root->left, doc_id);}
    else{return search(root->right, doc_id);}
}
int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
    TreeNode* ans = search(root, doc_id);
    if (ans){return ans->word_count;}
	return -1;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
    TreeNode* ans = search(root, doc_id);
    if (ans){return ans->name;}
	return 0;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
}
void delete(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    free(root->left);
    free(root->right);
    
    free(root->name);
    free(root->author);
    free(root);
}
void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
    delete(root);
}
