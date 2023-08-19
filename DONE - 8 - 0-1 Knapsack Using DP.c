#include<stdio.h>
#include<malloc.h>

//Function returns the maximum out of the two given values
int max(int a, int b){
    return a>=b?a:b;
}

//Function swaps two pointers whichhold a certain value
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//The function is fed with two arrays. it sorts the second array and alongwith swaps the positions in the first one as well
void sort(int *profit, int *weights, int n){
    int i, j;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if (weights[j]>weights[j+1]){
                swap(&weights[j], &weights[j+1]);
                swap(&profit[j], &profit[j+1]);
            }
        }
    }
}

//Actual program implementing the knapsack problem
int knapSack(int W, int *weights, int *profit, int n){
    int **knapTable;
    int i, j;

    knapTable = (int**)malloc((n+1)*sizeof(int*));  //Declaring a 2-D matrix for creating the DP table for the knapsack problem
    for(i=0; i<n+1; i++){
        knapTable[i] = (int*)malloc((W+1)*sizeof(int));
        for(j=0; j<W+1; j++){
            if(i==0 || j == 0)            //If we are in the first row or column (row 0 or col 0), we set that cell to zero
                knapTable[i][j] = 0;
            else{
                if(weights[i-1]<=j){    
                    knapTable[i][j] = max(knapTable[i-1][j], profit[i-1]+knapTable[i-1][j-weights[i-1]]);  //If the weight of the object of the current row is 
                    //less or equal to the permissible weight for that column (ie the val of j), then we have a choice to make. we choose the larger of the profits 
                    //among the profit earned in that column till the previous row (ie by not selecting the current item) and by selecting the item and getting
                    // the rest of the profit(ie W-weight[current row]) from the previous row items
                }
                else{
                    knapTable[i][j] = knapTable[i-1][j];  //If the current row item can't be included as its weight is more than the permissible weight for that col,
                    //we simply add the profit earned till the last row in that column as the profit for this row as well
                }
            }
        }
    }
    return knapTable[n][W];  //return the last cell of the last row as that's the answer
}

void main(){
    int n, i, maxWeight;
    int *profit, *weights;

    //Inputting the values
    printf("Enter the number of objects: ");
    scanf("%d", &n);

    profit = (int*)malloc(n*sizeof(int));
    weights = (int*)malloc(n*sizeof(int));

    printf("Enter the profits of objects: ");
    for(i=0; i<n; i++)
        scanf("%d", &profit[i]);
    printf("Enter the weights of objects: ");
    for(i=0; i<n; i++)
        scanf("%d", &weights[i]);
    printf("Enter the max weight permissible: ");
    scanf("%d", &maxWeight);
    //Inputting the values ends

    //sort the objects based on their weight
    sort(profit, weights, n);

    //print the max profit made!   
    printf("Max profit made: %d\n", knapSack(maxWeight, weights, profit, n));
}