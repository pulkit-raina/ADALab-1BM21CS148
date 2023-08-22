/*
Sort a given set of N integer elements using Heap Sort technique and compute its time taken
*/

#include <stdio.h>
#include <malloc.h>
#include <time.h>

// Function to heapify a subtree rooted at index i
void heapify(int *arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to perform Heap Sort
void heapSort(int *arr, int n) {
    int i, temp;

    // Build heap (rearrange array)
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract elements from heap
    for (i = n - 1; i >= 0; i--) {
        // Move current root to end
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    int n, i, *arr;
    clock_t start_time, end_time;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    arr = (int*)malloc(n*sizeof(n));

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

    printf("\nGiven array: ");
    for(i=0; i<n; i++)
        printf("%d ", arr[i]);
    start_time = clock(); // Start time of sorting

    heapSort(arr, n);

    end_time = clock(); // End time of sorting

    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nTime taken for sorting: %f seconds\n", time_taken);

    return 0;
}
