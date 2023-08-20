#include<stdio.h>
#include<malloc.h>
#define INF 99999

//This program used DSU (Disjoint Set Union) Data structure

//One of these structures represents one edge (ie. the two vertices and the weight of that edge
typedef struct edge{
    int i, j, w;
}edge;

//This function swaps two edge structures in an array
void swap(edge *a, edge *b){
    edge t = *a;
    *a = *b;
    *b = t;
}

//Function sorts an array of edge structure based on their edge weight using bubble sort
void sort(edge **el, int maxEdges){
    int i, j;
    for(i=0; i<maxEdges-1; i++){
        for(j=0; j<maxEdges-i-1; j++){
            if(el[j]->w > el[j+1]->w){

                swap(el[j], el[j+1]);
            }
        }
    }
}


//Takes the adjacency matrix as input (graph) and converts it into a list of edge structures (ie it stores the edge in the array el) and returns the number of edges
int convertToEdgeList(int **graph, int n, edge **el){
    int i, j, k=-1;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(i<j){        //since we are inputting an undirected graph, the value of edge is same from u to v as it is from v to u, so we consider only lower triangular matrix
                if(graph[i][j]!=INF){
                    el[++k]->i = i;
                    el[k]->j = j;
                    el[k]->w = graph[i][j];
                }
            }
        }
    }
    return k;   //Returns the index of the last edge inputted
}


//This is used to perform the union of two sets by changing their respective heads
void replace(int v1, int v2, int *set, int n){
    int i, x;

    //There are 4 possibilities for the vertices passed
    //Both can be -1, both can be a certain value, one -1 and other a certain value

    if(set[v1] == -1 && set[v2] == -1){  //If both are -1, set both of their heads to the lesser value vertex
        set[v1] = v1;
        set[v2] = v1;
    }
    else if(set[v1] == -1){             //If the smaller one is -1, set its head to the other value
        set[v1] = set[v2];
    }
    else if(set[v2] == -1){             //If the larger one is -1, set its head to the other value
        set[v2] = set[v1];
    }
    else{                               //If both of them are non-negative, we are merging two disjoint sets. So we change the head of all those vertices whose head is same as v2 to the head of v1
        x = set[v2];    //We store the actual value of set[v2] because it will be changed later and we can no longer use it then
        for(i=0; i<n; i++){
            if(set[i] == x){
                set[i] = set[v1];
            }
        }
    }
}

void main(){
    int n, i, j, k, maxEdges, head1, head2;
    int **graph, *set;
    edge **el;     //We create a pointer which points to an array of pointers, each of which are pointing to a structure containing the definition of an edge

    //Inputting the values
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    //If there are n vertices, at max there are nC2 edges, or max n*(n-1)/2 edges
    maxEdges = n*(n-1)/2;
    el = (edge**)malloc(maxEdges*sizeof(edge*));
    set = (int*)malloc(n*sizeof(int));
    for(i=0; i<maxEdges; i++)
        el[i] = (edge*)malloc(sizeof(edge));

    graph = (int**)malloc(n*sizeof(int*));
    printf("Enter the graph's adjacency matrix! Enter -1 for non-existant edge!\n");
    for(i=0; i<n; i++){
        graph[i] = (int*)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            scanf("%d", &graph[i][j]);
            if(graph[i][j] == -1){
                graph[i][j] = INF;
            }
        }
        set[i] = -1;           //Setting all vertices as not selected!
    }
    //Inputting completed!

    maxEdges = convertToEdgeList(graph, n, el) + 1;   //The function converts the given adjacency matrix of graph into a list of edges and returns the index of the last edge
    //maxEdges now represents the number of edges in the graphs

    //Sorts the edges based on their weights in increasing order
    sort(el, maxEdges);

    set[el[0]->i] = el[0]->i;
    set[el[0]->j] = el[0]->i;  //We mark the 2 vertices of the minimum edge as selected

    printf("\n\nMINIMUM SPANNING TREE\n");
    printf("%d to %d: %d\n", el[0]->i, el[0]->j, el[0]->w);

    k=0;
    while(k<n-2){   //Number of edges in minimum spanning tree is n-1, and one of them is already selected, is el[0]!
        for(i=0; i<maxEdges; i++){
            head1 = set[el[i]->i];
            head2 = set[el[i]->j];
            if((head1 != head2) || (head1 == -1 && head2 == -1)){
                printf("%d to %d: %d\n", el[i]->i, el[i]->j, el[i]->w);
                replace(el[i]->i, el[i]->j, set, n);
                k++;
                if(k==n-2)
                    break;
            }
        }
    }
}
