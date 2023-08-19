#include<stdio.h>
#include<malloc.h>

//This function merges any two given sorted arrays into one single array which is also sorted. 
//However we know that we need to merge the arrays from index l to m and m+1 to r (as those two sub-arrays are already sorted)
void merge(int *arr, int l, int m, int r){
    int n1, n2;
    int k1, k2, k; 
    int *newArr;

    n1 = m-l+1;
    n2 = r-m;

    newArr = (int*)malloc((n1+n2)*sizeof(int));

    k1 = l;
    k2 = m+1;
    k = 0;
    while(k1 != l+n1 && k2 != m+1+n2){
        if(arr[k1]<arr[k2]){
            newArr[k++] = arr[k1++];
        }
        else{
            newArr[k++] = arr[k2++];
        }
    }
    while(k1 != l+n1){
        newArr[k++] = arr[k1++];
    }
    while(k2 != m+1+n2){
        newArr[k++] = arr[k2++];
    }
    k = 0;
    while(k != n1+n2){
        arr[l+k] = newArr[k];
        k++;
    }
}

//This function finds the mid element of an array and calls merge sort on the left sub-array (l to m) and right sub-array (m+1 to r)
void mergeSort(int *arr, int l, int r){
    int m;
    if(l<r){
        m = (l+r)/2;
        mergeSort(arr, l, m);   //Sorting the left sub-array
        mergeSort(arr, m+1, r); //Sorting the right sub-array

        merge(arr, l, m, r);   //Merging the two sorted sub-arrays into one array
    }
}


int main(){
    int i, n;
    int *arr;

    //Inputting the values
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    arr = (int*)malloc(n*sizeof(int));
    printf("Enter the array!\n");
    for(i=0; i<n; i++)
        scanf("%d", &arr[i]);
    //Input intaking completed

    //Printing the given unsorted array
    printf("Given array: ");
    for(i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    //Implementing the mergeSort algorithm
    mergeSort(arr, 0, n-1);

    //Printing the sorted array
    printf("Sorted array: ");
    for(i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return -1;
}