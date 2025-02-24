#include<stdio.h>
struct router {
    unsigned distance[20];
    unsigned nextHop[20];
} routingTable[10];

int main() {
    int costMatrix[20][20];
    int totalNodes, i, j, k, updateCount = 0;
    printf("\nEnter the number of nodes: ");
    scanf("%d", &totalNodes);
    printf("\nEnter the cost matrix:\n");
    
    for(i = 0; i < totalNodes; i++) {
        for(j = 0; j < totalNodes; j++) {
            scanf("%d", &costMatrix[i][j]);
            costMatrix[i][i] = 0;
            routingTable[i].distance[j] = costMatrix[i][j];
            routingTable[i].nextHop[j] = j; 
        }
    }
    
    do {
        updateCount = 0;
        for(i = 0; i < totalNodes; i++) 
            for(j = 0; j < totalNodes; j++)
                for(k = 0; k < totalNodes; k++)
                    if(routingTable[i].distance[j] > costMatrix[i][k] + routingTable[k].distance[j]) {
                        routingTable[i].distance[j] = routingTable[i].distance[k] + routingTable[k].distance[j];
                        routingTable[i].nextHop[j] = k;
                        updateCount++;
                    }
    } while(updateCount != 0);

    for(i = 0; i < totalNodes; i++) {
        printf("\n\n For router %d\n", i + 1);
        for(j = 0; j < totalNodes; j++) {
            printf("\t\nnode %d via %d Distance %d ", j + 1, routingTable[i].nextHop[j] + 1, routingTable[i].distance[j]);
        }
    }
    printf("\n\n");
}

