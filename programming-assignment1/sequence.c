#include <stdio.h>
#include <stdlib.h>

static int pow3(int n){
    int result = 1;
    for (int i = 0; i < n; i++){
        result *= 3;
    }

    return result;
}

static void swap(long *a, long *b){
    long temp = *b;
    *b = *a;
    *a = temp;
}

static void bubblesort_sentinel(long *arr, int n){
    int last_swap = n - 1;
    int count = 0;
    while(last_swap >= 1){
        int new_last_swap = 0;
        for(int i = 0; i < last_swap; i++){
            if(arr[i] > arr[i+1]){
                swap(&arr[i], &arr[i+1]);
                new_last_swap = i;
            }
        }
    count ++;
    last_swap = new_last_swap;
    }
}

long *Generate_2p3q_Seq(int n, int *seq_size){
    long* seq;
    seq = (long *)malloc(sizeof(long));
    if(seq == NULL){
        return NULL;
    }
    *seq_size = 0;
    for(int p = 0; (1 << p) <= n; ++p){
        for(int q = 0; (1 << p) * pow3(q) <= n; ++q){
            seq = realloc(seq, (*seq_size + 1) * sizeof(long));
            if(seq == NULL){
                return NULL;
            }
            seq[*seq_size] = (1 << p) * pow3(q);
            (*seq_size)++;
        }
    }

    bubblesort_sentinel(seq, *seq_size);

    return seq;
}
