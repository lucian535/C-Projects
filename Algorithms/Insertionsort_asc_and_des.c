#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>


int insertionsort(int* x, int size, int (*compare)(int a, int b));
int ascending (int a, int b);
int descending (int a, int b);
void swap (int* num1, int* num2);


int main () {
    int x[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
    int size = sizeof(x)/sizeof(x[0]);
    printf("Number of Examinations: %d\n", insertionsort(x,size,ascending));

    for (int i = 0; i < size; i++) {
        printf("%d ", x[i]);
    } printf("\n");
    return 0;
}

int insertionsort(int* x, int size, int (*compare)(int a, int b)) {
    int comparison = 0;

    void swap (int* num1, int* num2);

    for (int i = 0; i < (size-1); i++) {
        for (int j = i+1; j > 0; j--) {
            comparison++;
            if (compare(x[j-1], x[j])) {
                swap(&x[j-1], &x[j]);
            } else {
                break;
            }
        }
    }
    return comparison;
}


void swap (int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int ascending (int a, int b) {
    return b < a;
}

int descending (int a, int b) {
    return b > a;
}

