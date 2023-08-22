/*
Implement all pair shortest paths problem using Floyd's algorithm
*/


#include<stdio.h>
#include<malloc.h>
#define INF 99999

//Finding the minimum of two elements
int min(int a, int b){
    return a>b?b:a;
}

//Implementing the main Floyd-Warshall algorithm
void floydWarshall(int **graph, int n){
    int i, j, k;

    for(k=0; k<n; k++){
        for(i=0; i<n; i++){
            for(j=0; j<n; j++){
                graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
            }
        }
    }
}

//Printing the matrix consisting of minimum distances between any 2 vertices
void printGraph(int **graph, int n){
    int i, j;

    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(graph[i][j] == INF){
                printf("INF ");
            }
            else{
                printf("%d ", graph[i][j]);
            }
        }
        printf("\n");
    }
}

void main(){
    int n, i, j;
    int **graph;

    //Input entering begins
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    graph = (int**)malloc(n*sizeof(int*));

    printf("Enter the adjacency matrix of graph! Enter -1 for non-existant edge!\n");
    for(i=0; i<n; i++){
        graph[i] = (int*)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            scanf("%d", &graph[i][j]);
            if(graph[i][j] == -1)
                graph[i][j] = INF;
        }
    }
    //Inpute entering ends

    //Main algorithm implementation
    floydWarshall(graph, n);
    printf("\nShortest Path graph's adjacency matrix is:\n");
    printGraph(graph, n);
}
