#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorting.h"

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

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Invalid arguments\n");
        return EXIT_FAILURE;
    }

    int size = 0;
    long *arr = Array_Load_From_File(argv[2], &size);

    if (arr == NULL) {
        printf("Failed to load array from file\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-a") == 0) {
        quickSort(arr, size);
    } else if (strcmp(argv[1], "-l") == 0) {
        mergeSort(arr, size);
    } else {
        free(arr);
        printf("Invalid option: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    int saved = Array_Save_To_File(argv[3], arr, size);
    free(arr);

    if (saved != size) {
        printf("Failed to save all elements to file\n");
        return EXIT_FAILURE;
    }

    printf("Successfully sorted and saved to file\n");
    return EXIT_SUCCESS;
}
