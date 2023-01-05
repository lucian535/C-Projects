/* 
Program based on the "Game of Life" simulation by John Conway
*/

#include <stdio.h>
#include <stdlib.h>

char cellTest (char *board, int w, int h, int x, int y) ;

void conwayStep ( char *board , int w, int h);

int main() {
    char board[] = {'1', '0', '1', '0', '1', '0', '0', '1', '0', '0', '1', '1', '0', '0', '1', '0', '1', '1'};
    int w = 6, h = 3;
    printf("=== BOARD ===\n");
    for (int k = 0; k < 3; k++) { // how many times the board will change
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                printf("[ ");
                printf("\033[0;31m"); 
                printf("%c ", board[j+i*w]);
                printf("\033[0m"); 
                printf("- ");
                printf("\033[0;32m");
                printf("(%d, %d) ", j, i);
                printf("\033[0m"); 
                printf("]");

            }
            printf("\n");
        }printf("\n");

        conwayStep(board, w, h);
    }

    return 0;
}

char cellTest (char *board, int w, int h, int x, int y) {
    //printf("neighbours of (%d, %d) are:\n", x,y);
    char * currentspot = &board[0] + x + w*y;
    //printf("current spot: %c\n", *currentspot);
    int alive = 0, dead = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((j!=0) || (i!=0)) {
                if ((x+i < w) && (x+i >= 0)) {
                    if ((y+j < h) && (y+j >= 0)) {
                        char * currentcheck = currentspot + (x+i)-x + w*((y+j)-y);
                        if (*currentcheck == '1') {
                            alive++;
                        } else {
                            dead++;
                        }
                        //printf("(%d, %d) -> %c\n", x+i, y+j, *currentcheck);
                    }
                }
            }
        }
    }
    if ((*currentspot == '1') && (alive<2)) {
        return '0';
    } else if ((*currentspot == '1') && (alive>3)) {
        return '0';
    } else if ((*currentspot == '0') && (alive==3)) {
        return '1';
    } else if ((*currentspot == '1') && ((alive==3) || (alive==2))) {
        return '1';
    }
    return *currentspot;
}

void conwayStep ( char *board , int w, int h) {
    char nextboard[w*h];
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            nextboard[j + i*w] = cellTest(board, w, h, j, i);
        }
    }
    for (int i = 0; i < w*h; i++) {
        board[i] = nextboard[i];
    }
}
