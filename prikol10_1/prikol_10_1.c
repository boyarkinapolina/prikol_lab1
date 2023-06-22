#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* arr;
    int frequency;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char* arr) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->arr = strdup(arr);
    newNode->frequency = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, char* arr) {
    if (root == NULL) {
        return createNode(arr);
    }
    if (strcmp(arr, root->arr) == 0) {
        root->frequency++;
    }
    else if (strcmp(arr, root->arr) < 0) {
        root->left = insert(root->left, arr);
    }
    else {
        root->right = insert(root->right, arr);
    }
    return root;
}

void DESC_order(struct Node* root) {
    if (root != NULL) {
        DESC_order(root->right);
        printf("%s - %d\n", root->arr, root->frequency);
        DESC_order(root->left);
    }
}

void ASC_order(struct Node* root) {
    if (root != NULL) {
        ASC_order(root->left);
        printf("%s - %d\n", root->arr, root->frequency);
        ASC_order(root->right);
    }
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->arr);
        free(root);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./a.exe <name_file> [-o ASC/DESC]\n");
        return 1;
    }
    char* name_file = argv[1];
    char* order_sort = "ASC";  
    if (argc > 2) {
        if (strcmp(argv[2], "-o") == 0) {
            if (argc > 3) {
                order_sort = argv[3];
            } else {
                printf("Usage: ./a. <name_file> [-o ASC/DESC]\n");
                return 1;}
        } else {
            printf("Usage: ./a <name_file> [-o ASC/DESC]\n");
            return 1;}
    }
    FILE* file = fopen(name_file, "r");
    if (file == NULL) {
        printf("Error: %s\n", name_file);
        return 1;
    }
    char arr[100];
    struct Node* root = NULL;
    while (fscanf(file, "%s", arr) == 1) {
        root = insert(root, arr);
    }
    fclose(file);
    if (strcmp(order_sort, "ASC") == 0) {
        ASC_order(root);
    } else if (strcmp(order_sort, "DESC") == 0) {
        DESC_order(root);} 
    else {
        printf("Invalid sort: %s\n", order_sort);
    }
    freeTree(root);
    return 0;
}