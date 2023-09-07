#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char **argv){
    if(argc != 4){
        return EXIT_FAILURE;
    }

    int size;
    long ncomp = 0;
    
    if(strcmp(argv[1], "-a") == 0){
        long *arr = Array_Load_From_File(argv[2], &size);
        if(arr == NULL){
            fprintf(stderr, "File load failure\n");
            return EXIT_FAILURE;
        }
        Array_Shellsort(arr, size, &ncomp);
        if(size == -1){
            fprintf(stderr, "Cannot open input file\n");
            return EXIT_FAILURE;
        }
        int num = Array_Save_To_File(argv[3], arr, size);
        free(arr);
        if(num <= -1){
            fprintf(stderr, "Open file failure\n");
            free(arr);
            return EXIT_FAILURE;
        }
        printf("%ld\n", ncomp);
        return EXIT_SUCCESS;
    }
    else if(strcmp(argv[1], "-l") == 0){
        Node *list = List_Load_From_File(argv[2]);
        if (list == NULL) {
            fprintf(stderr, "File load failure\n");
            return EXIT_FAILURE;
        }
        list = List_Shellsort(list, &ncomp);
        int num = List_Save_To_File(argv[3], list);
        while(list != NULL){
            Node *temp = list;
            list = list->next;
            free(temp);
        }
        if(num <= -1){
            fprintf(stderr, "Open file failure\n");
            return EXIT_FAILURE;
        }
        printf("%ld\n", ncomp);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
