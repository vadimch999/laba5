#include "header.h"

void getInt(int* a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n == 0) {
            printf("Incorrect input. Please, try again!");
            scanf("%*[^\n]");
        }

    } while (n == 0);
    scanf("%*c");
}

char* getstr() {
    char *ptr = (char *)malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0)
            scanf("%*c");
        else {
            len += strlen(buf);
            ptr = (char *)realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

void genlistAdj(node* adjlist, int n) {
    int random, xcoord, ycoord;
    node tmp;
    for (int i = 0; i < n; i++) {
        xcoord = rand() % 100;
        ycoord = rand() % 100;
        tmp.x = xcoord;
        tmp.y = ycoord;
        tmp.next = NULL;
        adjlist[i] = tmp;
        adjlist[i].ind = i;
    }
    node chosen;
    node *add;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            random = rand() % 2;
            if (random == 1 && i != j) {
                chosen = adjlist[j];
                xcoord = chosen.x;
                ycoord = chosen.y;
                if (adjlist[i].next == NULL) {
                    adjlist[i].next = (node*)malloc(sizeof(node));
                    adjlist[i].next->x = xcoord;
                    adjlist[i].next->y = ycoord;
                    adjlist[i].next->ind = j;
                 //   printf("!X: %d, Y: %d\n", adjlist[i].next->x, adjlist[i].next->y);
                }
                else {
                    add = (node*)malloc(sizeof(node));
                    add->x = xcoord;
                    add->y = ycoord;
                    add->next = adjlist[i].next;
                    adjlist[i].next = add;
                    add->ind = j;
                }
            }
        }
    }
}

void printList(node* adjlist, int n) {
    printf("\n");
    node *tmp;
    for (int i = 0; i < n; i++) {
        tmp = &adjlist[i];
        printf("Vertex #%d: X: %d, Y: %d\n", i + 1, tmp->x, tmp->y);
        while (tmp->next != NULL) {
            tmp = tmp->next;
            printf("X: %d, Y: %d, Index: %d\n", tmp->x, tmp->y, tmp->ind);
        }
       // printf("X: %d, Y: %d\n", tmp->x, tmp->y);
        printf("\n");
    }
}

void addNode(node** adjlist, int* n) {
    int x, y;
    printf("Enter the x coord: ");
    getInt(&x);
    printf("Enter the y coord: ");
    getInt(&y);
    for (int i = 0; i < *n; i++) {
        if ((*adjlist)[i].x == x &&  (*adjlist)[i].y == y) {
            printf("Error! It is impossible to add that vertex!\n");
            return;
        }
    }
    *adjlist = (node*)realloc(*adjlist, (*n + 1) * sizeof(node));
    (*adjlist)[*n].x = x;
    (*adjlist)[*n].y = y;
    (*adjlist)[*n].next = NULL;
    *n = *n + 1;
}

void addEdge(node* adjlist, int n) {
    int start, finish;
    printf("Enter the first vertex of the edge: ");
    getInt(&start);
    start--;
    printf("Enter the second vertex of the edge: ");
    getInt(&finish);
    finish--;
    if (start >= n || finish >= n || start < 0 || finish < 0) {
        printf("Incorrect input!\n");
        return;
    }
    node* tmp;
    tmp = &adjlist[start];
    do {
        if (tmp->ind == finish) {
            printf("Error! That edge is already exist!\n");
            return;
        }
        tmp = tmp->next;
    } while (tmp->next != NULL);
    node* add;
    add = (node*)malloc(sizeof(node));
    int dist = (adjlist[start].x - adjlist[finish].x) * (adjlist[start].x - adjlist[finish].x) + (adjlist[start].y - adjlist[finish].y) * (adjlist[start].y - adjlist[finish].y);
    printf("The square of the distance: %d\n", dist);
    add->x = adjlist[finish].x;
    add->y = adjlist[finish].y;
    add->next = adjlist[start].next;
    add->ind = finish;
    adjlist[start].next = add;
}