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
        adjlist[i].name = i;
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
                    adjlist[i].next->name = j;
                    adjlist[i].next->next = NULL;
                 //   printf("!X: %d, Y: %d\n", adjlist[i].next->x, adjlist[i].next->y);
                }
                else {
                    add = (node*)malloc(sizeof(node));
                    add->x = xcoord;
                    add->y = ycoord;
                    add->next = adjlist[i].next;
                    adjlist[i].next = add;
                    add->name = j;
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
        printf("Vertex #%d: X: %d, Y: %d\n", tmp->name + 1, tmp->x, tmp->y);
        while (tmp->next != NULL) {
            tmp = tmp->next;
            printf("X: %d, Y: %d, Name: %d\n", tmp->x, tmp->y, tmp->name + 1);
        }
       // printf("X: %d, Y: %d\n", tmp->x, tmp->y);
        printf("\n");
    }
}

void addNode(node** adjlist, int* n, int counter) {
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
    (*adjlist)[*n].name = counter;
    (*adjlist)[*n].next = NULL;
    *n = *n + 1;
}

void addEdge(node* adjlist, int n, int counter) {
    int start, finish, show = -1, fin = -1;
    printf("Enter the first vertex of the edge: ");
    getInt(&start);
    start--;
    printf("Enter the second vertex of the edge: ");
    getInt(&finish);
    finish--;
    if (start >= counter || finish >= counter || start < 0 || finish < 0 || (start == finish)) {
        printf("Incorrect input!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == start) {
            show = i;
            break;
        }
    }
    if (show == -1) return;
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == finish) {
            fin = i;
            break;
        }
    }
    if (fin == -1) return;
    node* tmp;
    tmp = &adjlist[show];
    while (tmp->next != NULL) {
        if (tmp->name == fin) {
            printf("Error! That edge is already exist!\n");
            return;
        }
        tmp = tmp->next;
    }
    if (tmp->name == fin) {
        printf("Error! That edge is already exist!\n");
        return;
    }
    node* add;
    add = (node*)malloc(sizeof(node));
    int dist = (adjlist[show].x - adjlist[fin].x) * (adjlist[show].x - adjlist[fin].x) + (adjlist[show].y - adjlist[fin].y) * (adjlist[show].y - adjlist[fin].y);
    printf("The square of the distance: %d\n", dist);
    add->x = adjlist[fin].x;
    add->y = adjlist[fin].y;
    add->next = adjlist[show].next;
    add->name = fin;
    adjlist[show].next = add;
}

void getInfo(node* adjlist, int n) {
    int start, finish;
    printf("Enter the first vertex of the edge: ");
    getInt(&start);
    start--;
    printf("Enter the second vertex of the edge: ");
    getInt(&finish);
    finish--;
    if (start >= n || finish >= n || start < 0 || finish < 0 || (start == finish)) {
        printf("Incorrect input!\n");
        return;
    }
    deleteEdge(adjlist, n, start, finish);
}

void deleteEdge(node* adjlist, int n, int start, int finish) {
    node* tmp;
    node* new;
    int show = -1;
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == start) {
            show = i;
            break;
        }
    }
    if (show == -1) return;
    tmp = &adjlist[show];
    while (tmp->next != NULL) {
        if (tmp->next->name == finish) {
            if (tmp->next->next != NULL) {
               new = tmp->next->next;
               free(tmp->next);
               tmp->next = new;
               return;
            }
            else {
                free(tmp->next);
                tmp->next = NULL;
                return;
            }
        }
        tmp = tmp->next;
    }
    // printf("Error! That edge was not found!\n");
}

void deleteGraph(node* adjlist, int n) {
    node* del;
    for (int i = 0; i < n; i++) {
        if (adjlist[i].next) {
            while (adjlist[i].next != NULL) {
                if (adjlist[i].next->next != NULL) {
                    del = adjlist[i].next->next;
                    free(adjlist[i].next);
                    adjlist[i].next = del;
                }
                else {
                    free(adjlist[i].next);
                    adjlist[i].next = NULL;
                }
            }
        }
    }
}

void deleteNode(node** adjlist, int* n) {
    int del, show = -1;
    printf("Enter the vertex which you want to delete: ");
    getInt(&del);
    del--;
    for (int i = 0; i < *n; i++) {
        if ((*adjlist)[i].name == del) {
            show = i;
            break;
        }
    }
    if (show == -1) return;
    node tmp;
    node *delete;
    tmp = (*adjlist)[show];
    (*adjlist)[show] = (*adjlist)[*n - 1];
    (*adjlist)[*n - 1] = tmp;
    if ((*adjlist)[*n - 1].next) {
        while ((*adjlist)[*n - 1].next != NULL)
        {
            if ((*adjlist)[*n - 1].next->next != NULL) {
                delete = (*adjlist)[*n - 1].next->next;
                free((*adjlist)[*n - 1].next);
                (*adjlist)[*n - 1].next = delete;
            }
            else {
                free((*adjlist)[*n - 1].next);
                (*adjlist)[*n - 1].next = NULL;
            }
        }
    }
    *adjlist = (node*)realloc(*adjlist, (*n - 1) * sizeof(node));
    *n = *n - 1;
    for (int i = 0; i < *n; i++) {
        deleteEdge(*adjlist, *n, (*adjlist)[i].name, show);
    }
}

void dfs(node* adjlist, int n) {
    int start, finish, show = -1, fin = -1;
    printf("Enter the first node: ");
    getInt(&start);
    printf("Enter the second node: ");
    getInt(&finish);
    start--;
    finish--;
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == start) {
            show = i;
            break;
        }
    }
    if (show == -1) return;
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == finish) {
            fin = i;
            break;
        }
    }
    if (fin == -1) return;
    int colors[n];
    for (int i = 0; i < n; i++) {
        colors[i] = 0;
    }
    dfs_check(adjlist, colors, n, show);
   /* for (int i = 0; i < n; i++) {
        printf("color #%d: %d\n", i + 1, colors[i]);
    } */
    if (colors[fin] == 2) {
        printf("It is possible to reach that node!\n");
    }
    else {
        printf("It is IMPOSSIBLE!!!\n");
    }
}

int find_ind(node *adjlist, int name, int n) {
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == name) {
            return i;
        }
    }
}

void dfs_check(node* adjlist, int* colors, int n, int ind) {
    colors[ind] = 1;
    node *tmp;
    int get_index;
    tmp = &adjlist[ind];
    if (tmp->next) {
        tmp = tmp->next;
        while (tmp->next != NULL) {
            get_index = find_ind(adjlist, tmp->name, n);
            if (colors[get_index] == 0) {
                dfs_check(adjlist, colors, n, get_index);
            }
            tmp = tmp->next;
        }
        get_index = find_ind(adjlist, tmp->name, n);
        if (colors[get_index] == 0) {
            dfs_check(adjlist, colors, n, get_index);
        }
    }
    colors[ind] = 2;
}

void bellman_ford(node* adjlist, int n) {
    int start, finish, show = -1, fin = -1, weight, get_index;
    printf("Enter the first node: ");
    getInt(&start);
    printf("Enter the second node: ");
    getInt(&finish);
    start--;
    finish--;
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == start) {
            show = i;
            break;
        }
    }
    if (show == -1) return;
    for (int i = 0; i < n; i++) {
        if (adjlist[i].name == finish) {
            fin = i;
            break;
        }
    }
    if (fin == -1) return;
    int dist[n];
    for (int i = 0; i < n; i++) {
        dist[i] = 1000000;
    }
    dist[show] = 0;
    node* tmp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            tmp = &adjlist[j];
            if (tmp->next) {
                tmp = tmp->next;
                while (tmp->next != NULL) {
                    weight = (adjlist[j].x - tmp->x) * (adjlist[j].x - tmp->x) + (adjlist[j].y - tmp->y) * (adjlist[j].y - tmp->y);
                    get_index = find_ind(adjlist, tmp->name, n);
                    if (dist[get_index] > dist[j] + weight) {
                        dist[get_index] = dist[j] + weight;
                    }
                    tmp = tmp->next;
                }
                get_index = find_ind(adjlist, tmp->name, n);
                weight = (adjlist[j].x - tmp->x) * (adjlist[j].x - tmp->x) + (adjlist[j].y - tmp->y) * (adjlist[j].y - tmp->y);
                if (dist[get_index] > dist[j] + weight) {
                    dist[get_index] = dist[j] + weight;
                }
            }
        }
    }
    if (dist[fin] == 1000000) {
        printf("It is IMPOSSIBLE!!!\n");
    }
    else {
        printf("The min distance: %d\n", dist[fin]);
    }
}