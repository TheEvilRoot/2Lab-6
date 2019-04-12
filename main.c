#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

int main() {
	
	BinaryTree *tree = emptyBinaryTree();
	if (tree == NULL) {
		printf("Tree is null\n");
		return 1;
	}

	btPush(tree, 1);
  
	btTraverse(tree);

	btPush(tree, 124);

	btTraverse(tree);

	btPush(tree, 123);
	btPush(tree, 126);
	btPush(tree,122);
	btPush(tree, 125);
	btPush(tree, 127);
	btPush(tree, 130);
  btPush(tree, -1);
  btPush(tree, -5);
  btPush(tree, -3);
	btDebug(tree);

	printf("%d\n", btFindAsymmetricalSubtrees(tree));
	return 0;
}
