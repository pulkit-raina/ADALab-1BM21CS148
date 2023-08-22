/*
Implement Johnson Trotter algorithm to generate permutations
*/

#include<stdio.h>
#include<malloc.h>

/*
Algorithm of Johnson Trotter:
i) Look for the greatest element which is greater than the adjacent element its direction points to. This is called the mobile element.
ii) Print the initial permutation and then swap the mobile element with its adjacent element to get the next permutation.
iii) If the mobile element just selected it not the greatest element in the array, swap the directions of the elements greater than the mobile element
iv) Repeat the process till you have no mobile element available
*/


//Function to swap the elements pointed to by a and b
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//Function to flip direction of all elements greater than the mobile element
void flipDirection(int *l, int *dir, int mobile, int n){
    int i;

    for(i=0; i<n; i++){
        if(l[i]>mobile){
            dir[i] = dir[i]*(-1);
        }
    }
}

//Function to get the mobile element in a given number array and a direction array
int getMobile(int *l, int *dir, int n){
    int i, maxMobile = -1, ind, k;   //Initialise maxMobile to -1, so that we can later compare it to the elements in the array(as elements in array are always positive)
    for(i=0; i<n; i++){
        k = i + dir[i];       //k now represents the index of element in direction of i and adjacent to it(since, dir[i] is -1 if element points to left, and +1 if it points to right)
        if(k>=0 && k<n){      //If this value of index (k) is within range of the array, ie it IS NOT out of bounds, go to the next step
            if(l[i]>l[k]){    //Check if the element at i, is greater than the element at k (ie element adjacent to it in direction of the element at i)
                if(maxMobile<l[i]){   //if previously selected maxMobile was greater, keep it else replace it with the new mobile
                    maxMobile = l[i];
                }
            }
        }
    }
    if(maxMobile == -1) //If a mobile element was never found (ie, it remained on its initialised value of -1, return -1 and stop the loop in the main function)
        return -1;
    for(i=0; i<n; i++){   //Else get the index of the maxMobile element and return the index
        if(l[i] == maxMobile){
            ind = i;
            break;
        }
    }
    return ind;
}

//Function to print the current permutation of the array and swap elements to get the next permutation
int perm(int n, int *dir, int *l){
    int m = getMobile(l, dir, n);   //m now represents the CURRENT index of the mobile element in the array (not yet swapped). It is -1 if no mobile element exists
    int i, pos;

    //Print the current permutation of the array
    for(i=0; i<n; i++)
        printf("%d ", l[i]);
    printf("\n");

    //If m == -1, ie no mobile element was found, return 0 and stop the while loop in the main function
    if(m == -1)
        return 0;

    //pos now represents the new position of the mobile element AFTER swapping it with the adjacent element
    pos = m + dir[m];

    swap(&l[m], &l[m+dir[m]]);     //Swap the mobile element in the number array
    swap(&dir[m], &dir[m+dir[m]]); //Swap the direction of the mobile element with its adjacent

    if (l[pos]<n)                  //If the value of the current mobile element is leser than the max element in the list, swap the directions of the elements greater than mobile
        flipDirection(l, dir, l[pos], n);
    return 1;
}

int main(){
    int n, i;
    int *l, *dir, cont = 1;

    //Input taking
    printf("Enter the value of n: ");
    scanf("%d", &n);

    l = (int*)malloc(n*sizeof(int));
    dir = (int*)malloc(n*sizeof(int));

    for(i=0; i<n; i++){
        l[i] = i+1;       //Creating the array of initial permutation, eg: if n = 4, l = [1, 2, 3, 4] initially
        dir[i] = -1;      //directions of all the elements is set to -1 (ie. left to right) first
    }

    while(cont){            //cont is initialised to 1
        cont = perm(n, dir, l);    //the funct perm returns 1 if a new permutation was generated successfully, else -1 is returned and cont is set to -1, thus stopping the loop
    }
}
