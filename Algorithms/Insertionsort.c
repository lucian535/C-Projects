#include <stdio.h>
#include <assert.h>
#include <math.h>


int insertionsort(int* x, int size);

int main () {
    int x[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
    int size = sizeof(x)/sizeof(x[0]);
    printf("%d \n", insertionsort(x,size));
    return 0;
}

int insertionsort(int* x, int size) {
    int placeholder, comparison=0;
    for (int i = 0; i < (size-1); i++) {
        for (int j = i+1; j > 0; j--) {
            comparison++;
            if (x[j] < x[j-1]) {
                placeholder = x[j-1];
                x[j-1] = x[j];
                x[j] = placeholder;
            } else {
                break;
            }
        }
    }
    return comparison;
}
