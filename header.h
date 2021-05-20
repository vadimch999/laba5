#ifndef LABA5_HEADER_H
#define LABA5_HEADER_H

#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define msg "0. Quit \n1. Add node\n2. Print\n3. Add edge\n4. Delete edge\n5. Delete node\n6. Find node\n7. Belmann-Ford\n8. Ford-Fulkerson\n9. Timing\n10. Load file\n11. Save file\n"

typedef struct node {
    int x;
    int y;
    int name;
    struct node* next;
} node;



void getInt(int *a);
char* getstr();
void genlistAdj(node* adjlist, int n);
void printList(node* adjlist, int n);
void addNode(node** adjlist, int* n, int counter, int x, int y);
void addEdge(node* adjlist, int show, int fin);
void deleteEdge(node *adjlist, int n, int start, int finish);
void deleteGraph(node* adjlist, int n);
void deleteNode(node** adjlist, int* n);
void getInfo(node* adjlist, int n);
void dfs(node* adjlist, int n, int show, int fin);
void dfs_check(node* adjlist, int* colors, int n, int ind);
int find_ind(node *adjlist, int name, int n);
void bellman_ford(node* adjlist, int n, int show, int fin);
void Ford_Falkerson(node* adjlist, int n);
int timing_func();
void start_bellman_ford(node* adjlist, int n);
void start_dfs(node* adjlist, int n);
void dfs_check_modified(node* adjlist, int* colors, int n, int ind);
void getInfoNode(node *adjlist, int* n, int counter);
void getInfoEdge(node* adjlist, int n, int counter);
int load(node **root);
void save_edges(node* adjlist, int n, FILE *fd);
void save_nodes(node* adjlist, int n, FILE* fd);
int save(node* root, int n);

#endif //LABA5_HEADER_H
