#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

int comparePayload(payload i, payload j) {
  return j - i;
}

// Printing a payload (ex. int)
void printPayload(payload p){ 
	printf("%d\n", p); 
}

BinaryTreeNode * newNode(payload data) {
	BinaryTreeNode *node = (BinaryTreeNode*) calloc(1, sizeof(BinaryTreeNode));
	
	if (node == NULL) {
		return NULL;
	}
	
	node->data = data;

	return node;
}

BinaryTree * emptyBinaryTree() {
	BinaryTree *tree = (BinaryTree*) calloc(1, sizeof(BinaryTree));

	if (tree != NULL) {
		tree->root = NULL;
	}
	return tree;
}

BinaryTree * binaryTreeOf(payload *items, int count) {
	BinaryTree *tree = emptyBinaryTree();

	if (tree == NULL) {
		return NULL;
	}
	
	for (int i = 0; i < count; i++) {
		btPush(tree, items[i]);
	}

	return tree;
}

void btPush(BinaryTree *tree, payload data) {
	if (tree == NULL) {
		return;
	}

	if (tree->root == NULL) {
		tree->root = newNode(data);
	} else {
		bnPush(tree->root, data);
	}
}

void bnPush(BinaryTreeNode *node, payload data) {
	if (node == NULL) {
		return;
	}
	
	int delta = comparePayload(node->data, data);

	// node->data is less then data
	if (delta < 0) { 
		if (node->left == NULL) {
			node->left = newNode(data);
		} else {
			bnPush(node->left, data);
		}
	} else if (delta > 0){
		if (node->right == NULL) {
			node->right = newNode(data);
		} else {
			bnPush(node->right, data);
		}
	}
}

void btTraverse(BinaryTree *tree) {
	if (tree == NULL) {
		return;
	}

	if (tree->root != NULL) {
		bnTraverse(tree->root);
	}
}

void btDebug(BinaryTree *tree) {
  if (tree == NULL) {
    printf("Tree is NULL\n");
    return;
  }
  
  printf("Tree at 0x%x\n", tree);
  bnDebug(tree->root, 0);
}

void bnDebug(BinaryTreeNode *node, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("\t");
  }
  if (node == NULL) {
    printf("NULL node\n");
    return;
  }
  printf("Node %d at 0x%x\n", node->data, node);
  
  if (node->left != NULL) {
    bnDebug(node->left, depth + 1);
  }
  
  if (node->right != NULL) {
    bnDebug(node->right, depth + 1);
  }
}

void bnTraverse(BinaryTreeNode *node) {
	if (node == NULL) {
		return;
	}

	if (node->left != NULL) {
		bnTraverse(node->left);
	}
	
	printPayload(node->data);

	if (node->right != NULL) {
		bnTraverse(node->right);
	}
}

int bnCountChildren(BinaryTreeNode *node) {
	if (node == NULL) {
		return 0;
	}

	int ret = 0;
	if (node->left != NULL) {
		ret += 1 + bnCountChildren(node->left);
	}
	if (node->right != NULL) {
		ret += 1 + bnCountChildren(node->right);
	}
	return ret;
}

int bnIsAsymmetrical(BinaryTreeNode *node) {
	// Edge cases: 
	// 	* node is null - then it isn't symmetric one
	//	* node is empty - it also is not symmtric
	if (node == NULL) {
		return 0;
	}
	
	if (node->left == NULL && node->right == NULL) {
		return 0;
	}

	int leftSide = node->left != NULL ? 1 + bnCountChildren(node->left) : 0;
	int rightSide = node->right != NULL ? 1 + bnCountChildren(node->right) : 0;

	return leftSide - rightSide != 0;
}

int bnFindAsymmetricalSubtrees(BinaryTreeNode *root, int **valuesPtr, int *countPtr) {
	int self = bnIsAsymmetrical(root);
	int left = root->left == NULL ? 0 : bnFindAsymmetricalSubtrees(root->left, valuesPtr, countPtr);
	int right = root->right == NULL ? 0 : bnFindAsymmetricalSubtrees(root->right, valuesPtr, countPtr);

	if (self > 0) {
	    countPtr[0]++;
	    valuesPtr[0] = realloc(valuesPtr[0], sizeof(int) * countPtr[0]);
	    valuesPtr[0][countPtr[0] - 1] = root->data;
	}

	return self + left + right;
}

int * btFindAsymmetricalSubtrees(BinaryTree *tree, int *countPtr) {
	if (tree == NULL) {
		return 0;
	}

	if (tree->root == NULL) {
		return 0;
	}

	int *values = (int*) calloc(1, sizeof(int));
	int count = 0;

	bnFindAsymmetricalSubtrees(tree->root, &values, &count);

	*countPtr = count;
	return values;
}
