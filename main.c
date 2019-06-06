#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

char * enterString(const char *message) {
    char *string = (char*) calloc(1,  sizeof(char));

    if (string == NULL) {
        return NULL;
    }

    int i = 0;
    char c;

    printf("%s", message);

    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    while ((c = (char) getchar()) != -1) {
        string[i++] = c;

        if (c == '\n') {
            string[i - 1] = '\0';
            break;
        }

        if (!(string = (char*) realloc(string, sizeof(char) * (i + 1)))) {
            break;
        }
    }

    return string;
}


unsigned int isNumber(char c) {
    return c >= '0' && c <= '9';
}

int power(int num, int power) {
    int ret = 1;
    for (; power > 0; power--) {
        ret *= num;
    }

    return ret;
}

int toNumber(char c) {
    return c - '0';
}


int stringLength(char *string) {
    int len = 0;
    for (; string[len] != '\0'; ++len);
    return len;
}

void analizeInput(char *string, int length, BinaryTree *tree) {
    for (int i = 0; i < length; i++) {
        char c = string[i];

        if (isNumber(c)) {
            int numPower = 0;
            int number = 0;
            int numStart = i;

            for (; i < length && isNumber(string[i]); i++);
            // i = numEnd

            for (int q = i - 1; q >= numStart; q--, numPower++) {
                number += toNumber(string[q]) * power(10, numPower);
            }

            btPush(tree, number);
        }
    }
}

int main() {
    BinaryTree *tree = emptyBinaryTree();
    if (tree == NULL) {
        printf("Ow.. Failed to create binary tree. Memory?\n");
        return 1;
    }

    printf("Let's enter tree...\n");
    printf("Enter numbers to push into the tree. Enter # to finish\n");

    do {
        char *inputString = enterString("> ");
        if (inputString == NULL) {
            printf("Sorry. Input failed. Try again\n");
            continue;
        }
        int length = stringLength(inputString);
        if (length == 0) continue;
        if (inputString[0] == '#') break;

        analizeInput(inputString, length, tree);
    } while (1);
    printf("Ok. You added %d numbers\n", bnCountChildren(tree->root) + 1);

    btTraverse(tree);

    printf("Asymmetric nodes has values: \n");
    int count = 0;
    int * values = btFindAsymmetricalSubtrees(tree, &count);
    if (count == 0 || values == NULL) {
        printf("\tNo such nodes in this tree\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("* %d\n", values[i]);
        }
    }
    return 0;
}
