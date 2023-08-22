/*
Write a program to obtain the Topological ordering of vertices in a given digraph
*/

#include<stdio.h>
#include<malloc.h>

//Implementing the DFS function
void dfs(int source, int **graph, int *visited, int n, int *result, int *res_ind){
    int i;
    visited[source] = 1;

    for(i=0; i<n; i++){
        if(graph[source][i] && !visited[i]){
            dfs(i, graph, visited, n, result, res_ind);
        }
    }
    result[(*res_ind)++] = source;
}

//Implementing the topological ordering function
int* topological(int n, int **graph, int *visited){
    int i;
    int *res, res_ind = 0;

    res = (int*)malloc(sizeof(int));
    for(i=0; i<n; i++){
        if(!visited[i]){
            dfs(i, graph, visited, n, res, &res_ind);
        }
    }
    return res;
}

int main(){
    int i, j, n;
    int **graph;
    int *visited, *res;

    //Input entering begins
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    visited = (int*)malloc(n*sizeof(int));
    graph = (int**)malloc(n*sizeof(int*));

    printf("Enter the adjacency matrix!\n");
    for(i=0; i<n; i++){
        visited[i] = 0;
        graph[i] = (int*)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            scanf("%d", &graph[i][j]);
        }
    }
    //input intaking ends

    //Processing the graph for getting the topological order
    res = topological(n, graph, visited);
    for(i=n-1; i>=0; i--)
        printf("%d->", res[i]);
    printf("END\n");
    return -1;
}
