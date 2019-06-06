#ifndef _binary_tree_h
#define _binary_tree_h

#include <stdio.h>

struct bt_node {
	int data;

	struct bt_node *left;
	struct bt_node *right;
};

struct bt {
	struct bt_node *root;
};

typedef struct bt_node BinaryTreeNode;
typedef struct bt BinaryTree;

BinaryTreeNode * newNode(int data);
BinaryTree * emptyBinaryTree(void);

void btPush(BinaryTree *tree, int data);
void bnPush(BinaryTreeNode *node, int data);

void btTraverse(BinaryTree *tree);
void bnTraverse(BinaryTreeNode *node);

int bnCountChildren(BinaryTreeNode *node);

int bnIsAsymmetrical(BinaryTreeNode *node);

int bnFindAsymmetricalSubtrees(BinaryTreeNode *root,int **valuesPtr, int *countPtr);
int * btFindAsymmetricalSubtrees(BinaryTree *tree, int *countPtr);

#endif
