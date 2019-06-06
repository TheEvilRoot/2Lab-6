#ifndef _binary_tree_h
#define _binary_tree_h

#include <stdio.h>

#define payload int

// Comparing payload (ex. int)
int comparePayload(payload i, payload j);

// Printing a payload (ex. int)
void printPayload(payload p);

struct bt_node {
	payload data;

	struct bt_node *left;
	struct bt_node *right;
};

struct bt {
	struct bt_node *root;
};

typedef struct bt_node BinaryTreeNode;
typedef struct bt BinaryTree;

BinaryTreeNode * newNode(payload data);
BinaryTree * emptyBinaryTree(void);
BinaryTree * binaryTreeOf(payload *items, int count);

void btPush(BinaryTree *tree, payload data);
void bnPush(BinaryTreeNode *node, payload data);

void btTraverse(BinaryTree *tree);
void bnTraverse(BinaryTreeNode *node);

void btDebug(BinaryTree *tree);
void bnDebug(BinaryTreeNode *node, int depth);

int bnCountChildren(BinaryTreeNode *node);

int bnIsAsymmetrical(BinaryTreeNode *node);

int bnFindAsymmetricalSubtrees(BinaryTreeNode *root,int **valuesPtr, int *countPtr);
int * btFindAsymmetricalSubtrees(BinaryTree *tree, int *countPtr);

#endif
