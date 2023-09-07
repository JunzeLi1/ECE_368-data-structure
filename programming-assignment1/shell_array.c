#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

long *Array_Load_From_File(char *filename, int *size){
    FILE *fp;
    if((fp = fopen(filename, "rb")) == NULL){
        *size = 0;
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    *size = file_size / sizeof(long);
    long *arr = (long *)malloc(*size * sizeof(long));
    if (arr == NULL){
        *size = 0;
        return NULL;
    }
    fseek(fp, 0, SEEK_SET);
    fread(arr, sizeof(long), *size, fp);
    fclose(fp);

    return arr;
}

int Array_Save_To_File(char *filename, long *array, int size){
    FILE *fp;
    if((fp = fopen(filename, "wb")) == NULL){
        size = 0;
        return 0;
    }
    if(array == NULL || size == 0){
        fclose(fp);
        return 0;
    }
    int num_long = fwrite(array, sizeof(long), size, fp);
    fclose(fp);

    return num_long;
}

static void Insertion_sort(long *array, int size, long *n_comp, int  gap){
    for(int i = gap; i < size; i++){
        long temp = array[i];
        int j;
        for(j = i; j >= gap && array[j - gap] > temp; j -= gap){
            array[j] = array[j - gap];
            (*n_comp)++;
        }
        array[j] = temp;
    }
}

void Array_Shellsort(long *array, int size, long *n_comp){
    long *seq;
    int seq_size;
    seq = Generate_2p3q_Seq(size, &seq_size);
    for(int i = seq_size - 1; i >= 0; i --){
        Insertion_sort(array, size, n_comp, seq[i]);
    }
    free(seq);
}

