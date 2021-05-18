#ifndef LABA5_HEADER_H
#define LABA5_HEADER_H

#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define msg "0. Quit \n1. Add node\n2. Print\n3. Add edge\n4. Delete edge\n5. Delete node\n"

typedef struct node {
    int x;
    int y;
    int ind;
    struct node* next;
} node;

void getInt(int *a);
char* getstr();
void genlistAdj(node* adjlist, int n);
void printList(node* adjlist, int n);
void addNode(node** adjlist, int* n);
void addEdge(node* adjlist, int n);
void deleteEdge(node *adjlist, int n, int start, int finish);
void deleteGraph(node* adjlist, int n);
void deleteNode(node** adjlist, int* n);
void getInfo(node* adjlist, int n);

#endif //LABA5_HEADER_H
