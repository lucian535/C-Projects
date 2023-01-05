/* 
Program to compute the collatz conjecture of numbers from 1-99 and to create a tree like data structure
*/

#include <stdio.h>
#include <stdlib.h>


struct collatzNode {
    struct collatzNode *even;
    struct collatzNode *odd;
    int value;
};


int * Collatz(int n);

void construct(struct collatzNode ** tree, int * chain, int lastNumber); // need to pass by double reference because were not retruning it, implict return

int deconstructTree(struct collatzNode ** tree);

int writeTreeToGraphviz(struct collatzNode * tree, char * filename);

int main() {

    struct collatzNode * urmom = malloc(sizeof(struct collatzNode));
    urmom->value = 1;
    urmom->even = NULL;
    urmom->odd = NULL;

    for (int i = 1; i <= 20; i++){
        int * x;
        x = Collatz(i);

        construct(&urmom, x, i);
    }
    printf("Deconstructing\n");
    writeTreeToGraphviz(urmom, "deez.txt");
    deconstructTree(&urmom);


    return 0;
}

int * Collatz(int n) {
    int currentnum = n;
    int * x = malloc(sizeof(int));
    x[0] = n;
    int size = 1;
    while (currentnum != 1) {
        if (currentnum%2 == 0) { // even
            currentnum = currentnum/2;
        } else { // odd
            currentnum = 3*currentnum + 1;
        }
        size++;
        x = realloc(x, sizeof(int)*size);
        x[size-1] = currentnum;
    }

    for (int i = 0; i < size/2; i++) {
        int temp = x[i];
        x[i] = x[size-1-i];
        x[size-1-i] = temp;
    }
    printf("collatz for %d:\n",n);
    for (int i = 0; i < size; i++) {
        printf("%d, ", x[i]);
    }printf("\n\n");

    return x;
}


/* Creates the collatz node tree with the given arrays */

void construct(struct collatzNode ** tree, int * chain, int lastNumber) {
    int index = 0;

    struct collatzNode *currentpos = *tree;
    printf("===================\nCHECKING n = %d\n===================\n", lastNumber);
    printf("Traversing through tree, starting at 1\n");
    
    while (chain[index] != lastNumber) {
        index++; // start chacking at index 1
        if (chain[index] % 2 == 0) { //even
            if (currentpos->even == NULL) { // if the even branch doesnt exist, then we add it
                currentpos->even = malloc(sizeof(struct collatzNode));
                currentpos->even->even = NULL;
                currentpos->even->odd = NULL;
                currentpos->even->value = chain[index];
                currentpos = currentpos->even;
                printf("Currently at %d, making a new even branch\n", chain[index]);
            } else { // if it exists then we just traverse it
                currentpos = currentpos->even;
                printf("Currently at %d, branch exists, travelling\n", chain[index]);
            }
        } else { //odd
            if (currentpos->odd == NULL) { // if the even branch doesnt exist, then we add it
                currentpos->odd = malloc(sizeof(struct collatzNode));
                currentpos->odd->even = NULL;
                currentpos->odd->odd = NULL;
                currentpos->odd->value = chain[index];
                currentpos = currentpos->odd;
                printf("Currently at %d, making a new odd branch\n", chain[index]);
            } else { // if it exists then we just traverse it
                currentpos = currentpos->odd;
                printf("Currently at %d, branch exists, travelling\n", chain[index]);
            }
        }
    }
    printf("\n\n");
}

int deconstructTree(struct collatzNode ** tree) {
    struct collatzNode * ptr = *tree;
    if (ptr == NULL) {
        return 0;
    } 
    deconstructTree(&(ptr->even));
    deconstructTree(&(ptr->odd));
    //printf("%d\n", (*tree)->value);
    free(ptr);
    return 0;
}

/* Writes the data from the struct to a file */
int writeTreeToGraphviz(struct collatzNode * tree, char * filename) {
    static int counter = 0;
    int nope = 1;
    FILE *fp;
    
    if (tree == NULL) {
        return 0;
    }
    if (counter == 0) {
        if ((fp = fopen(filename, "w")) == NULL) {
		    return 0;
        }
        counter++;
        nope = 0;
        fprintf(fp, "digraph a {\n");
        fclose(fp);
    } 
    if ((fp = fopen(filename, "a")) == NULL) {
		return 0;
    } 
    
    if (tree->even != NULL) {
        fprintf(fp, "\t%d -> %d\n", tree->even->value, tree->value);
    }
    int i = writeTreeToGraphviz(tree->even, "deez.txt");
    if (tree->odd != NULL) {
        fprintf(fp, "\t%d -> %d\n", tree->odd->value, tree->value);
    }
    int j = writeTreeToGraphviz(tree->odd, "deez.txt");

    printf("%d\n", tree->value);

    if (tree->value == 1) {
        printf("nope");
        //fprintf(fp,"}");
    }

    return 0;

}
