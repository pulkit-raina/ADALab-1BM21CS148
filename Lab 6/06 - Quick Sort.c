/*
Sort a given array of N integer elements using Quick Sort technique and compute its time taken
*/

#include<stdio.h>
#include<malloc.h>
#include<time.h>

//Function for swapping two values(pointers) given
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Main QuickSort function
void quickSort(int *arr, int l, int r){
    if(l!=r){ //If l==r, means only 1 element in the sub-array, so no need to sort
        int i = l, j = r;
        int pivot = l;
        while(i<j){
            while(arr[i]<=arr[pivot]){
                if (i==r)
                    break;
                i++;
            }
            while(arr[j]>arr[pivot]){
                if (j==l)
                    break;
                j--;
            }
            if(i<j){
                swap(&arr[i], &arr[j]);     //This swap brings all elements lesser than pivot to the left, and all greater than it to the right
            }
        }
        swap(&arr[j], &arr[pivot]);    //This swap brings the pivot element to its correct position
        if(j!=l)
            quickSort(arr, l, j-1);     //Calls the quicksort function on the left sub-array of the pivot only if the current pivot is NOT the left most element
        if (j!=r)
            quickSort(arr, j+1, r);    //Calls the quicksort function on the right sub-array of the pivot only if the current pivot is NOT the right most element
    }
}


int main(){
    int i, n;
    int *arr;
    time_t start_time, end_time;

    //Input entering begins
    printf("Enter the size of array: ");
    scanf("%d", &n);

    arr = (int*)malloc(n*sizeof(int));
    if(n>10){                   //If number of elements are too large, eg 500, 1000, we take random values using the rand() function
        for(i=0; i<n; i++)
            arr[i] = rand()%9999;
    }
    else{
        printf("Enter the array!\n");
        for(i=0; i<n; i++)
            scanf("%d", &arr[i]);
        //Input intaking completed
    }

    //Printing the current array
    printf("Given array is: ");
    for(i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    start_time = clock();

    //Calling the quicksort function on the whole array, ie. from 0 to n-1
    quickSort(arr, 0, n-1);

    end_time = clock();

    //Printing the sorted array
    printf("Sorted array is: ");
    for(i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Total time taken = %f seconds", (double)(end_time - start_time)/CLOCKS_PER_SEC);
    return -1;
}
