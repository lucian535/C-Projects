#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>


int shellsort (int *array, int size, int *h_gaps, int (*subsort)(int* array, int size));
int bubblesort(int* x, int size);


int bubblesort(int* x, int size) {
    int temp;
    int swaps = 0;
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (x[j] > x[j+1]) {
                temp = x[j];
                x[j] = x[j + 1];
                x[j+1] = temp;
                swaps ++;
            }
        }
    }
    return swaps;
}


int main () {
    int x[] = {135, 529, 81, 54, 46, 605, 47, 793, 278, 323, 306, 430, 973, 286, 712, 962, 461, 81, 57,
325, 711, 995, 833, 222, 284, 293, 153, 224, 126, 643, 425, 400, 420, 309, 831, 6, 496, 347, 185, 583};
    int size = sizeof(x)/sizeof(x[0]);
    int hgaps[] = {10, 4, 1};

    printf("Number of sorts: %d\n ", shellsort(x,size,hgaps,bubblesort));

    for (int i = 0; i < size; i++) {
        printf("%d ", x[i]);
    } printf("\n");
    
    return 0;
}

int shellsort (int *array, int size, int *h_gaps, int (*subsort)(int* array, int size)) {
    int totalswaps = 0, hgapindex = 0,currenthgap;
    do {
        currenthgap = h_gaps[hgapindex];
        int subarraysize = ceil((float)size/(currenthgap));
        int **subarrays = (int**)malloc(sizeof(int*) * (currenthgap));
        for (int i = 0; i < currenthgap; i++) {
            subarrays[i] = (int*)malloc(sizeof(int) * subarraysize);
        }
        if (subarrays == NULL) {
            return -1;
        }
        int l = 0, k = 0;
        for (int counter = 0; counter < size; counter++) {
            subarrays[l][k] = array[counter];
            l++;
            if (l>currenthgap-1) {
                l=0; k++;
            }
        }
        int cutoffnum = (size-1)%(currenthgap);
        for (int j = 0; j < currenthgap; j++) {
            totalswaps += subsort(subarrays[j],(j>cutoffnum) ? (subarraysize-1) : subarraysize);
        }
        l = 0; k = 0;
        for (int counter = 0; counter < size; counter++) {
            array[counter] = subarrays[l][k];
            l++;
            if (l>currenthgap-1) {
                l=0; k++;
            }
        }
        free(subarrays);
        hgapindex++;
    } while (currenthgap > 1);
    return totalswaps;
}
