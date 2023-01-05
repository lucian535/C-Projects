/*
Program to parse strings of equations and return the value of the computed equation
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int simpleParse(const char *exp);



int main() {
    char exp1[] = "1 + 1";
    char exp2[] = "3 + 7 - 4 * 1";
    char exp3[] = "9 * 13 / 2 + 18 * 110 - 812 % 97 + 3";
    
    
    printf("%s = %d\n", exp1, simpleParse(exp1));
    printf("%s = %d\n", exp2, simpleParse(exp2));
    printf("%s = %d\n", exp3, simpleParse(exp3));

    char eq[] = "2*20*22 -0   + 7/2     -8%3 + 7*20*20 -   40/2/4";
    //char eq[100];
    //scanf("%s", eq);
    printf("%s = %d\n", eq, simpleParse(eq));
}

int simpleParse(const char *exp) {
    char working[strlen(exp) + 1]; strcpy(working, exp);
    char ops2[] = "+-", * token, operation, legaloperations[] = "+-/*%";
    int firstnum = 1, numop1, numop2, tokeniterations = 0, sum = 0;
    token = strtok(working, ops2);
    while (token != NULL) {
        int numnumbers = 0, startcount = 0, operationcount = 0;;
        char * dumper = malloc(sizeof(char)*strlen(token));
        tokeniterations++;
        numop1 = strtol(token, &dumper, 10);
        for (int i = 0; i < strlen(token)+1; i++) {
            if (isdigit(*(token+i))) {
                startcount = 1;
            }
            for (int j = 0; j < 5; j++) {
                if ((isspace(*(token+i)) || (*(token+i+1) == '\0') || (*(token+i) == legaloperations[j])) && startcount) {
                    numnumbers++;
                    startcount = 0;
                }
            }
        }
        //printf("%s\n", token);
        if (numnumbers > 1) {
            while (strlen(dumper) > 0) {
                for (int i = 0; i < strlen(dumper); i++){
                    if ((!isdigit(*(dumper+i))) && (!isspace(*(dumper+i)))) {
                        operation = *(dumper+i);
                        numop2 = strtol(dumper+i+1, &dumper, 10);
                        if (operation == '*') {
                            numop1 = numop1 * numop2;
                        } else if (operation == '/') {
                            if (numop2 == 0) {
                                return -1;
                            } else {
                                numop1 = numop1 / numop2;
                            }
                        } else if (operation == '%') {
                            numop1 = numop1 % numop2;
                        }
                        numnumbers--;
                        if (numnumbers == 1) {
                            strcpy(dumper,"");
                        }
                        break;
                    }
                }
            }
        } 
        //printf("CALC: %d\n", numop1);
        if (tokeniterations > 1) {
            int j = 0;
            while (exp[j] != '\0'){
                if ((exp[j] == '+') || (exp[j] == '-')) {
                    operationcount++;
                }
                if (operationcount == (tokeniterations - 1)) {
                    if (exp[j] == '+') {
                        sum = sum + numop1;
                    } else if (exp[j] == '-') {
                        sum = sum - numop1;
                    }
                    break;
                }
                j++;
            }
        } else {
            sum = numop1;
        }
        token = strtok(NULL, ops2);
    }
    return sum;
}
