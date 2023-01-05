/* 
Program to find the longest max repeated sequence in an array
*/

#include <stdio.h>
#include <stdlib.h>

int sumSequence(int * start, int * end);

int compareSequences(int * start1, int * end1, int * start2, int * end2);

int maxRepeatedSequence(int * array, int arraysize, int ** seq1, int ** seq2, int * size);

int main() {
    int x[] = {1,2,3,4,5,6,7,8,4,5,6,7,8,9,10};
    int size = sizeof(x)/sizeof(x[0]);

    int * seq1, * seq2, subarraysize;

    printf("Max Repeated sum: %d\n", maxRepeatedSequence(x, size, &seq1, &seq2, &subarraysize));
    printf("seq1: %p -> %d, seq2: %p -> %d, size: %d\n", seq1, *seq1, seq2, *seq2, subarraysize);

    return 0;
}

int sumSequence(int * start, int * end) {
    int sum = 0;
    for (int * i = start; i < end + 1; i++) {
        sum += *i;
    }
    return sum;
}

int compareSequences(int * start1, int * end1, int * start2, int * end2) {
    if ((end1-start1) != (end2-start2)) {
        return 0;
    }

    for (int i = 0; i < (end1 - start1 + 1); i++) {
        if (*(start1 + i) != *(start2 + i)) {
            return 0;
        }
    }

    //printf("Sequence sum: %d\n", sumSequence(start1, end1));

    return 1;
}

int maxRepeatedSequence(int * array, int arraysize, int ** seq1, int ** seq2, int * size) {
    int maxsum = 0;
    for (int i = 0; i < arraysize-1; i++) { // itereates through the entire array , left most number
        int * pos1 = array + i; // initializes its position, starts at the 0 index
        for (int j = i + 1; j < arraysize; j++) { // for loop to intereate through the rest of the array, starting right after pos1
            int * pos2 = array + j; // initializing pos2 to be 1 position to the right of pos1
            if (*pos1 == *pos2) { // keeps going and checks if the number at pos1 and pos2 are equal
                int * end1 = pos1; // sets their end points to the original pointers which will be manipulated later
                int * end2 = pos2;

                while(compareSequences(pos1, end1, pos2, end2)) { // keeps comparing the 2 seuqneces until they are no longer identical
                    if (sumSequence(pos1, end1) > maxsum) { // checks the sum of each sequence and if its bigger than maxsum
                        maxsum = sumSequence(pos1, end1); // max sum gets reassigned tot he larger sum
                        *seq1 = pos1; // implict return of pos1 and pos2 and size of the sub sequence
                        *seq2 = pos2;
                        *size = end1-pos1+1;
                    }
                    if ((end2 + 1) < array + arraysize) { // checks to see if we can keep adding 1 index to pos2 since its on the right to check if it reaches thee nd fo teh array
                        end1 = end1 + 1; // adds one to end1 and end2 which will then run through the compare function again to see if they are still identical
                        end2 = end2 + 1;
                    } else { // if it reaches the end then it breaks out of the while loop
                        break;
                    }
                }
            }
        }
    }
    return maxsum;
}
