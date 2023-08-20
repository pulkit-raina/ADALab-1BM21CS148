#include<stdio.h>
#include<malloc.h>
#define INF 99999


void main(){
    int **graph, *selected;
    int n, i, j, k, x, y, minDistance, sum = 0;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    selected = (int*)malloc(n*sizeof(int));

    printf("Enter the adjacency matrix of the graph! Enter -1 if no path exists!\n");
    graph = (int**)malloc(n*sizeof(int*));
    for(i=0; i<n; i++){
        graph[i] = (int*)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            scanf("%d", &graph[i][j]);
            if(graph[i][j] == -1){
                graph[i][j] = INF;
            }
        }
        selected[i] = 0;
    }

    selected[0] = 1;   //Make the 1st vertex as selected

    printf("\n\nMINIMUM SPANNING TREE\n");
    //In each iteration of this for loop we add one edge to the minimum spanning tree
    for(k=0; k<n-1; k++){   //k is repeated for n-1 times, as the number of edges in a minimum spanning tree is n-1

        //We need to get the vertice adjacent to the currently selected vertex
        minDistance = INF;
        x = 0;
        y = 0;

        for(i=0; i<n; i++){
            if(selected[i]){
                //This checks all those vertices that are already selected and the adjacent vertices to them
                for(j=0; j<n; j++){     //This loop now finds the distances between the current i vertex and every other non-selected vertex
                    if(!selected[j] && graph[i][j]){
                        if(graph[i][j]<minDistance){
                            minDistance = graph[i][j];   //Minimum distance for the current selected vertex (ie k vertex)
                            x = i;              //x is one of the vertices of the minimum distance
                            y = j;              //y is other vertex of the minimum distance
                        }
                    }
                }
            }
        }

        printf("%d to %d: %d\n", x, y, graph[x][y]);
        sum += graph[x][y];
        selected[y] = 1;
    }
    printf("\nTotal cost of the tree: %d", sum);
}
