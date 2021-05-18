#include "header.h"

int main() {
    srand(time(NULL));
    int n = 10;
    printf("Enter the size of the graph: ");
    getInt(&n);
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
                addNode(&adjlist, &n);
                break;
            case 2:
                printList(adjlist, n);
                break;
            case 3:
                addEdge(adjlist, n);
                break;
            case 4:
                getInfo(adjlist, n);
                break;
            case 5:
                deleteNode(&adjlist, &n);
                break;
            default:
                printf("Error!\n");
        }
    } while(command != 0);
    free(adjlist);
    return 0;
}
