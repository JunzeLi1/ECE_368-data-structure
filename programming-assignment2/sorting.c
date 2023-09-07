#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"

void printArr(long* arr, int size)
{
    for(int i = 0; i < size; i++){
        printf("%ld", arr[i]);
    }
    printf("\n");
}

static int median_of_three(long* arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) {
        long temp = arr[mid];
        arr[mid] = arr[low];
        arr[low] = temp;
    }
    if (arr[high] < arr[low]) {
        long temp = arr[high];
        arr[high] = arr[low];
        arr[low] = temp;
    }
    if (arr[high] < arr[mid]) {
        long temp = arr[high];
        arr[high] = arr[mid];
        arr[mid] = temp;
    }
    return mid;
}

int partition(long* arr, int lb, int ub)
{
    if (ub < lb) {
        return -1;
    }

    int pivotIndex = median_of_three(arr, lb, ub);
    long pivotValue = arr[pivotIndex];
    long temp = arr[pivotIndex];
    arr[pivotIndex] = arr[ub];
    arr[ub] = temp;

    int i = lb - 1;
    int j = ub;

    while (1) {
        do {
            ++i;
        } while (arr[i] < pivotValue);
        do {
            --j;
        } while (j >= lb && arr[j] > pivotValue);
        
        if (i >= j) {
            break;
        }
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    temp = arr[i];
    arr[i] = arr[ub];
    arr[ub] = temp;

    return i;
}

void quickSort(long* arr, int size)
{
    if (size < 2) {
        return;
    }
    int pivotIndex = partition(arr, 0, size - 1);
    if (pivotIndex > 0) {
        quickSort(arr, pivotIndex);
    }
    if (pivotIndex + 1 < size) {
        quickSort(arr + pivotIndex + 1, size - pivotIndex - 1);
    }
}

void merge(long* src, long* dest, int lb, int mid, int ub)
{
    if (ub <= lb || mid < lb || mid + 1 > ub) {
        return;
    }

    int i = lb, j = mid + 1, k = lb;

    while (i <= mid && j <= ub) {
        if (src[i] <= src[j]) {
            dest[k++] = src[i++];
        } else {
            dest[k++] = src[j++];
        }
    }

    while (i <= mid) {
        dest[k++] = src[i++];
    }

    while (j <= ub) {
        dest[k++] = src[j++];
    }

    for (i = lb; i <= ub; i++) {
        src[i] = dest[i];
    }
}

static void mergesort_helper(long* src, long* dest, int lb, int ub) {
    if (ub > lb) {
        int mid = lb + (ub - lb) / 2;

        mergesort_helper(src, dest, lb, mid);
        mergesort_helper(src, dest, mid + 1, ub);

        merge(src, dest, lb, mid, ub);
    }
}

void mergeSort(long* src, int size)
{
    long* aux = (long*) malloc(size * sizeof(long));

    if (aux == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return;
    }

    mergesort_helper(src, aux, 0, size - 1);

    free(aux);
}

/*
int main() {
    // Create a test array
    long arr[] = {5, 1, 9, 3, 7, 6, 8, 2, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Print the array before sorting
    printf("Before sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("%ld ", arr[i]);
    }
    printf("\n");

    // Sort the array
    mergeSort(arr, size);

    // Print the array after sorting
    printf("After sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("%ld ", arr[i]);
    }
    printf("\n");

    long arr1[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    quickSort(arr1, n);
    
    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%ld ", arr1[i]);
    }
    printf("\n");


    return 0;
}
*/