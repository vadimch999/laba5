#include "header.h"

int main() {
    srand(time(NULL));
    int n, counter;
    printf("Enter the size of the graph: ");
    getInt(&n);
    counter = n;
    node* adjlist = (node*)malloc(n * sizeof(node));
   genlistAdj(adjlist, n);
    int command;
    do {
        printf("%s", msg);
        printf("Enter your choice: ");
        getInt(&command);
        switch(command) {
            case 0:
                deleteGraph(adjlist, n);
                break;
            case 1:
                getInfoNode(adjlist, &n, counter);
                counter++;
                printf("N: %d\n", n);
                break;
            case 2:
                printList(adjlist, n);
                break;
            case 3:
                getInfoEdge(adjlist, n, counter);
                break;
            case 4:
                getInfo(adjlist, n);
                break;
            case 5:
                deleteNode(&adjlist, &n);
                printf("N: %d\n", n);
                break;
            case 6:
                start_dfs(adjlist, n);
                break;
            case 7:
                start_bellman_ford(adjlist, n);
                break;
            case 8:
                Ford_Fulkerson(adjlist, n);
                break;
            case 9:
                timing_func();
                break;
            case 10:
                deleteGraph(adjlist, n);
                n = load(&adjlist);
                break;
            case 11:
                save(adjlist, n);
                break;
            default:
                printf("Error!\n");
        }
    } while(command != 0);
    free(adjlist);
    return 0;
}
