#include<stdio.h>
#include<malloc.h>

//Making a queue
typedef struct queue{
    int *nodes;
    int f;
    int r;
}queue;

//Initiaiting the Queue
queue* initQueue(queue *q){
    q->f = 0;
    q->r = 0;
    return q;
}

//insert an element into the queue
queue* enterQueue(queue *q, int i){
    q->nodes[(q->r)++] = i;
    return q;
}

//remove an element from queue
int removeQueue(queue *q){
    return q->nodes[(q->f)++];
}

//Check if the queue is empty
int empty(queue *q){
    if (q->f == q->r)
        return 1;
    return 0;
}

//print the reachable nodes, and unreachable nodes, if any
void print(queue *q, int n, int *visited){
    int i, j, flag = 1;
    printf("Nodes reachable are: ");
    for(i=0; i<q->r; i++){
        printf("%d->",q->nodes[i]);
    }
    printf("END");
    for(i=0; i<n; i++){
        if (visited[i] == 0){
            flag = 0;
            printf("\n\nUnvisited nodes exist!\nUnvisited Nodes: ");
            for(j=i; j<n; j++){
                printf("%d ", visited[j]);
            }
            break;
        }
    }
    if(flag == 1){
        printf("\n\nNo unreachable nodes from given source node!\n");
    }
}

//Main BFS implementation function
void bfs(queue *q, int *visited, int **graph, int n){
    int source, i;
    printf("Enter the source vertice between 1 and %d: ", n);
    scanf("%d", &source);
    
    q = enterQueue(q, source);
    while(!empty(q)){
        source = removeQueue(q);
        visited[source-1] = 1;
        for(i=0; i<n; i++){
            if(graph[source-1][i]==1 && !visited[i]){
                q = enterQueue(q, i+1);
                visited[i] = 1;
            }
        }
    }
}

int main(){
    int **graph;
    int *visited;
    int n, i, j;
    queue *q = malloc(sizeof(*q));

    //Input taking begins
    printf("Enter the size of the digraph: ");
    scanf("%d", &n);

    printf("Enter the digraph!\n");
    graph = (int**)malloc(n*sizeof(int*));
    visited = (int*)malloc(n*sizeof(int));
    q = initQueue(q);
    q->nodes = (int*)malloc(n*sizeof(int));

    for(i=0; i<n; i++){
        graph[i] = (int*)malloc(n*sizeof(int));
        for(j=0; j<n; j++){
            scanf("%d", &graph[i][j]);
        }
        visited[i] = 0;
    }
    //Input taking ends
    
    bfs(q, visited, graph, n);
    
    print(q, n, visited);
    return -1;    
}