/*
From a given vertex in a weighted connected graph, find shortest paths to other vertices using Dijkstra's algorithm
*/

#include<stdio.h>
#include<malloc.h>
#define INF 99999

//Function to return the minimum of 2 intergers
int min(int a, int b){
    return a<=b?a:b;
}

//Function to implement the Dijkstra's algorithm
void dijkstra(int **graph, int source, int n){
    int distance[n], visited[n];   //Distance matrix stores the values of distances between the source and every other vertex
    //visited array stores whether a node has been visited or not

    int i, j, minDistance, nextNode; /*minDistance is set to infinity at start and during the iteration,
    the vertices which is closest to the currently selected vertice is found*/

    //Now we set the distance of every vertice from the source as per the input matrix (ie direct distance between source and vertex
    for(i=0; i<n; i++){
        distance[i] = graph[source][i];
        visited[i] = 0;                //Set every vertex as 0 (not visited)
    }

    distance[source] = 0;         //distance from source to source is 0
    visited[source] = 1;        //the source vertex is now visited

    /*this for loop runs for n-2 times (ie from 0 to n-3).
    We don't run it for n times because the source vertex is already selected and the last node will be automatically selected*/
    for(i=0; i<n-2; i++){
        minDistance = INF;

        //This for loop finds the vertex nearest to the source (since distance[i] is distance between i and source)
        for(j=0; j<n; j++){
            if(distance[j] < minDistance && !visited[j]){
                minDistance = distance[j];
                nextNode = j;
            }
        }
        //nextNode here now represents the node closest to the source

        //nextNode is now visited
        visited[nextNode] = 1;

        /*Next for loop checks whether distance between source and any other vertex
        is lesser (ie distance[i]) or distance from source to nextNode + nextNode to other vertex is lesser*/
        for(j=0; j<n; j++){
            if(!visited[j]){
                distance[j] = min(distance[j], minDistance + graph[nextNode][j]);
            }
        }

        //With completion of this iteration, one vertex (closest to the source is selected and visited completed. Next the second closest will be selected
        //This is similar to the Floyd-Warshall algorithm
    }


    //Printing the distance between any two vertices
    for(i=0; i<n; i++){
        if(i != source){
            printf("Distance from %d to %d is %d\n", source+1, i+1, distance[i]);
        }
    }
}

int main(){
    int **graph;
    int n, i, j, source;

    //Inputting the graph
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    graph = (int**)malloc(n*sizeof(int*));

    printf("Enter the adjacency matrix of the graph! If no path exists, enter -1!\n");
    for(i=0; i<n; i++){
        graph[i] = (int*)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            scanf("%d", &graph[i][j]);
            if(graph[i][j] == -1){
                graph[i][j] = INF;
            }
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);
    //Inputting ends


    dijkstra(graph, source-1, n);   //we subtract 1 from the source to adjust for the 0-indexing in the arrays

    return -1;
}
