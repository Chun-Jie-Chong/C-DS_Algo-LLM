/* Certainly! Below is an implementation of the bubble sort algorithm in C, and it includes the necessary headers: */
/*  */
/* ```c */
#include <stdio.h>

// Function to swap two elements
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// int main() {
//     int arr[] = {64, 34, 25, 12, 22, 11, 90};
//     int n = sizeof(arr)/sizeof(arr[0]);
//     printf("Unsorted array: \n");
//     printArray(arr, n);
//     bubbleSort(arr, n);
//     printf("Sorted array: \n");
//     printArray(arr, n);
//     return 0;
// }
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Unable to open file");
        return 1;
    }

    int arr[1000];
    int n = 0;

    while (fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }
    fclose(file);

    bubbleSort(arr, n);

    printArray(arr, n);
    return 0;
}
/* ``` */
/*  */
/* Here's a brief explanation of the code: */
/* 1. **swap**: This function swaps two integers given their addresses. */
/* 2. **bubbleSort**: This function implements the bubble sort algorithm. It consists of a nested loop where the inner loop repeatedly steps through the list, compares adjacent items, and swaps them if they are in the wrong order. The outer loop ensures this process is repeated for all elements. */
/* 3. **printArray**: This utility function prints the array elements. */
/* 4. **main**: The entry point of the program. It defines an array, prints it unsorted, calls the `bubbleSort` function to sort the array, and then prints the sorted array. */
/*  */
/* To compile and run this program, you can use any standard C compiler. For example, using GCC: */
/* ```sh */
/* gcc bubble_sort.c -o bubble_sort */
/* ./bubble_sort */
/* ``` */
