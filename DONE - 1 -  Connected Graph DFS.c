#include<stdio.h>
#include<malloc.h>

void dfs_second(int source, int **graph, int *visited, int n){
    int i;
    for(i=0; i<n; i++){
        if(graph[source][i] && !visited[i]){
            visited[i] = 1;
            dfs_second(i, graph, visited, n);
        }
    }
}

int dfs(int source, int **graph, int n){
    int *visited;
    int i, count = 0;

    visited = (int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        visited[i] = 0;
    }
    visited[source] = 1;

    for(i=0; i<n; i++){
        if(graph[source][i] && !visited[i]){
            visited[i] = 1;
            dfs_second(i, graph, visited, n);
        }
    }
    
    for(i=0; i<n; i++)
        if(visited[i])
            count += 1;
    return count;
}

int main(){

    //Input taking
    int n, i, j, count, flag = 0;
    int **graph;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    graph = (int**)malloc(n*sizeof(int*));

    printf("Enter the adjacency matrix!\n");
    for(i=0; i<n; i++){
        graph[i] = (int*)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            scanf("%d", &graph[i][j]);
        }
    }
    //Inputs taken

    //Checking if nodes are reachable
    for(i=0; i<n; i++){
        count = dfs(i, graph, n);
        if(count == n){
            flag = 1;
            printf("All nodes are reachable via source %d\n", i+1);
            break;
        }
    }
    
    //If all nodes aren't reached, print it's disconnected
    if(!flag){
        printf("The graph is disconnected!\n");
    }

    return -1;
}