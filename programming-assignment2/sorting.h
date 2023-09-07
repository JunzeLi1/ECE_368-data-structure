#ifndef __HELPER_FUNCS__
#define __HELPER_FUNCS__

int partition(long* arr, int lb, int ub);
void merge(long* src, long* dest, int lb, int mid, int ub);

#endif

#ifndef __SORTING_FUNCS__
#define __SORTING_FUNCS__

void quickSort(long* arr, int size);
void mergeSort(long* arr, int size);

#endif

void printArr(long* arr, int size);