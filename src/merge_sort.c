/* Certainly! Below is an implementation of the merge sort algorithm in C, along with the necessary headers: */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>

// Function to merge two subarrays of arr[]
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k++] = R[j++];
    }

    // Free the allocated memory
    free(L);
    free(R);
}

// Function that implements merge sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test above functions
// int main() {
//     int arr[] = {12, 11, 13, 5, 6, 7};
//     int arr_size = sizeof(arr) / sizeof(arr[0]);

//     printf("Given array is \n");
//     printArray(arr, arr_size);

//     mergeSort(arr, 0, arr_size - 1);

//     printf("Sorted array is \n");
//     printArray(arr, arr_size);
//     return 0;
// }
/* ``` */
/*  */
/* **Explanation:** */
/* 1. **Including Headers:** */
/*    - `#include <stdio.h>` for input and output functions. */
/*    - `#include <stdlib.h>` for dynamic memory allocation using `malloc` and `free`. */
/*  */
/* 2. **Merge Function:** */
/*    - This function merges two subarrays of `arr[]`. The first subarray is `arr[left..mid]` and the second subarray is `arr[mid+1..right]`. */
/*  */
/* 3. **Merge Sort Function:** */
/*    - This is a divide-and-conquer approach that recursively divides the array into two halves, sorts them, and then merges them. */
/*  */
/* 4. **Print Array Function:** */
/*    - Utility function to print the array elements. */
/*  */
/* 5. **Main Function:** */
/*    - Initializes an array and prints it. */
/*    - Calls `mergeSort` to sort the array. */
/*    - Prints the sorted array. */
/*  */
/* Compile and run this code to see merge sort in action! */
