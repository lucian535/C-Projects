#include <stdio.h>
#include <assert.h>
#include <math.h>


int bubblesort(int* x, int size);

int main () {
    int x[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
    int size = sizeof(x)/sizeof(x[0]);
    printf("%d \n", bubblesort(x,size));
    return 0;
}

int bubblesort(int* x, int size) {
    int placeholder, swaps=0;
    for (int i = 0; i < (size-1); i++) {
        for (int j = 0; j < (size-i-1); j++) {
            if (x[j] > x[j+1]) {
                placeholder = x[j+1];
                x[j+1] = x[j];
                x[j] = placeholder;
                swaps ++;
            }
        }
    }
    return swaps;
}
