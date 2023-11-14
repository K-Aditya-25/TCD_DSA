#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct definition
struct bstnode {
    int   doc_id;           // unique identifier for the document
    char *name;           // file name of the document    
	char* author;         //author of the document
    int word_count;       // number of words in the document
	int height;      
    struct bstnode *left;
	struct bstnode *right; // pointer to the next node in the list
};

//global variables
int g_next_id;     // ID of the next document to be added
struct bstnode *root; // database storage

float g_num_comps;
float g_num_searches;
int num_insert;
int count_nodes;

//----------------------------------Custom Functions-----------------------------------
struct bstnode* tree_search(struct bstnode* root,int doc_id){

    if(root->doc_id==doc_id || root==NULL){
    return root;
	g_num_comps++;
    }
  
    if(root->doc_id < doc_id)
	{g_num_comps++;
    return tree_search(root->right,doc_id);}
	
    
    else
	{g_num_comps++;
    return tree_search(root->left,doc_id);}
	
}
int height(struct bstnode *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

struct bstnode *rightRotate(struct bstnode *y)
{
    struct bstnode *x = y->left;
    struct bstnode *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
     return x;
}
struct bstnode *leftRotate(struct bstnode *x)
{
    struct bstnode *y = x->right;
    struct bstnode *T2 = y->left;
     y->left = x;
    x->right = T2;
     x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
     return y;
}


int getBalance(struct bstnode *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

struct bstnode* createbst(int doc_id, char *name, char* author, int word_count, struct bstnode *root){
	
	count_nodes++;
	/* If the tree is empty, return a new node */
	if (root == NULL)
		{
			struct bstnode* newnode=(struct bstnode*)malloc(sizeof(struct bstnode));
		newnode->doc_id=doc_id;
		newnode->name=name;
		newnode->author = author;
		newnode->word_count=word_count;
		newnode->height=1;
        newnode->left=NULL;
        newnode->right=NULL;
		return newnode;
		}



	/* Otherwise, recur down the tree */
	else
	{
	if (doc_id < root->doc_id)
	{
		root->left=createbst (doc_id, name , author, word_count,root->left);	
	}
	else if(doc_id > root->doc_id)
		{
			
		root->right=createbst(doc_id, name, author, word_count,root->right);	
		}

     else return root;
	}

    root->height = 1 + max(height(root->left),height(root->right)); 
    int balance = getBalance(root);
 
    // Left Left Case
    if (balance > 1 && doc_id < root->left->doc_id)
        return rightRotate(root);
     // Right Right Case
    if (balance < -1 && doc_id > root->right->doc_id)
        return leftRotate(root);
     // Left Right Case
    if (balance > 1 && doc_id > root->left->doc_id)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
     // Right Left Case
    if (balance < -1 && doc_id < root->right->doc_id)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
int isBalanced(struct bstnode* root)
{
    /* for height of left subtree */
    int lh;
 
    /* for height of right subtree */
    int rh;
 
    /* If tree is empty then return true */
    if (root == NULL)
        return 1;
 
    /* Get the height of left and right sub trees */
    lh = height(root->left);
    rh = height(root->right);
 
    if (abs(lh - rh) <= 1 && isBalanced(root->left)
        && isBalanced(root->right))
        return 1;
 
    /* If we reach here then tree is not height-balanced */
    return 0;
}

int totalNodes(struct bstnode* root)
{
    if (root == NULL)
        return 0;
 
    int l = totalNodes(root->left);
    int r = totalNodes(root->right);
 
    return 1 + l + r;
}
void tree_delete(struct bstnode *root){
    if (root == NULL) return;
    tree_delete(root->left);
    tree_delete(root->right);
    free(root);
}

//-------------------------------------Program Functions------------------------------
int bstdb_init ( void ) {
	root =NULL;
    g_next_id = 0;
    g_num_comps = 0;
    g_num_searches = 0;
	num_insert=0;
	return 1;
}


int bstdb_add (char *name, int word_count, char* author) {
	num_insert++;
	struct bstnode *newnode;
	newnode=createbst(g_next_id, name, author, word_count, root);
	if(!newnode){return -1;}
	root=newnode;
	return g_next_id++;
}


int bstdb_get_word_count ( int doc_id ) {
	struct bstnode *ans; 
	g_num_searches++;
    ans = tree_search(root,doc_id);
	if(ans==NULL)
	return -1;

	else
	return ans->word_count;
}

char* bstdb_get_name ( int doc_id )
{
	struct bstnode *ans; 
	g_num_searches++;
    ans = tree_search(root,doc_id);
	if(ans==NULL)
	return "-1";

	else
	return ans->name;
}

void
bstdb_stat ( void ) {

	int a=isBalanced(root);
	if(a==1)
	printf("Tree is balanced\n");
	else
	printf("Tree is not balanced\n"); 

	
	//check total number of nodes = total nodes in BST
    int n=totalNodes(root);
	if(n==num_insert)
	printf("Tree size matches expected? Yes\n");

	else
	printf("Tree size matches expected? No\n");

	//print average comparisons per search
    printf("Average comparisons per search = %f\n",(g_num_comps/g_num_searches));
	
	//print height of tree
	int h=height(root);
	printf("Height of the tree = %d\n",h);
}

void bstdb_quit ( void ) {
tree_delete(root);
}
