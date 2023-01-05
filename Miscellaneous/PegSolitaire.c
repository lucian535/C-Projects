/*
Game of Peg solitaire
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printBoard(const int board[7][7]); 

int parseMove(char *input, int *x1, int *y1, int *x2, int *y2);
int isValidMove(const int board[7][7], char *input);
void effectMove(int board[7][7], char *input);
int isWon(const int board[7][7]);

int parseMove(char *input, int *x1, int *y1, int *x2, int *y2) {
	char letters[] = "ABCDEFGHIJKLMNOPxponmlkjihgfedcba";
	int xcoord[] = {5,4,3,5,4,3,7,6,5,4,3,2,1,7,6,5,4,3,2,1,7,6,5,4,3,2,1,5,4,3,5,4,3};
	int ycoord[] = {1,1,1,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,7,7,7};

	int index = -1;
	for (int j = 0; j < 33; j++) {
		if (input[0] == letters[j]) {
			index = j;
			break;
		}
	}
	if (index == -1) {
		return -1;
	}
	*x1 = xcoord[index];
	*y1 = ycoord[index];

	int index2 = -1;
	for (int j = 0; j < 33; j++) {
		if (input[1] == letters[j]) {
			index2 = j;
			break;
		}
	}
	if (index2 == -1) {
		return -1;
	}
	*x2 = xcoord[index2];
	*y2 = ycoord[index2];

	return 0; 
}

int isValidMove(const int board[7][7], char *input) {
	char letters[] = "abcdefghijklmnopxPONMLKJIHGFEDCBA";
	int xcoord[] = {0,0,0,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,6,6,6};
	int ycoord[] = {2,3,4,2,3,4,0,1,2,3,4,5,6,0,1,2,3,4,5,6,0,1,2,3,4,5,6,2,3,4,2,3,4};

	int x1,y1,x2,y2;
	
	int valid1 = 0;
	for (int i = 0; i < 33; i++) {
		if (input[0] == letters[i]) {
			x1 = xcoord[i];
			y1 = ycoord[i];
			//printf("board[%d][%d] = %d\n",x1,y1, board[x1][y1]);
			if (board[x1][y1] == 1) { // checks to  see that the first letter is a valid space with a pin
				valid1 = 1;
			}
			break;
		}
	}
	if (!valid1) {
		return 0;
	}

	//printf("(x1, y1) = (%d, %d)\n", x1,y1);

	int valid2 = 0;
	for (int i = 0; i < 33; i++) {
		if (input[1] == letters[i]) {
			x2 = xcoord[i];
			y2 = ycoord[i];
			//printf("board[%d][%d] = %d\n",x2,y2, board[x2][y2]);
			if (board[x2][y2] == 0) { // checks to see if the second item is a free space
				valid2 = 1;
			}
			break;
		}
	}
	if (!valid2) {
		return 0;
	}
	//printf("(x2, y2) = (%d, %d)\n", x2,y2);

	int xdiff, ydiff;
	xdiff = x2-x1;
	ydiff = y2-y1;

	//printf("xdiff: %d ydiff: %d\n", xdiff, ydiff);

	if (abs(xdiff+ydiff) != 2) {
		return 0;
	}
	//printf("board[%d][%d]\n", x1 + (int)(xdiff/2), y1 + (int)(ydiff/2));
	if (board[x1 + (int)(xdiff/2)][y1 + (int)(ydiff/2)] == 1) {
		return 1;
	}
	return 0;
}

void effectMove(int board[7][7], char *input) {
	char letters[] = "abcdefghijklmnopxPONMLKJIHGFEDCBA";
	int xcoord[] = {0,0,0,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,6,6,6};
	int ycoord[] = {2,3,4,2,3,4,0,1,2,3,4,5,6,0,1,2,3,4,5,6,0,1,2,3,4,5,6,2,3,4,2,3,4};

	int x1,y1,x2,y2;

	for (int i = 0; i < 33; i++) {
		if (input[0] == letters[i]) {
			x1 = xcoord[i];
			y1 = ycoord[i];
			break;
		}
	}

	for (int i = 0; i < 33; i++) {
		if (input[1] == letters[i]) {
			x2 = xcoord[i];
			y2 = ycoord[i];
			break;
		}
	}

	board[x1][y1] = 0; board[x2][y2] = 1;

	int xdiff, ydiff;
	xdiff = x2-x1;
	ydiff = y2-y1;

	board[x1 + (int)(xdiff/2)][y1 + (int)(ydiff/2)] = 0;
}

int isWon(const int board[7][7]) {
	int onecount = 0, winningspot = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (board[i][j] == 1) {
				onecount++;
			}
		}
	}
	if (board[3][3] == 1) {
		winningspot = 1;
	}
	if (winningspot && (onecount == 1)) {
		return 1;
	}
	return 0;
}



int main () {
	char buffer[50];
	int board[7][7] = {	{2, 2, 1, 1, 1, 2, 2}
					  , {2, 2, 1, 1, 1, 2, 2}
					  , {1, 1, 1, 1, 1, 1, 1}
					  , {1, 1, 1, 0, 1, 1, 1}
					  , {1, 1, 1, 1, 1, 1, 1}
					  , {2, 2, 1, 1, 1, 2, 2}
					  , {2, 2, 1, 1, 1, 2, 2}
					  };

// */ // Winning board 
/*					{	{2, 2, 0, 0, 0, 2, 2}
					  , {2, 2, 0, 0, 0, 2, 2}
					  , {0, 0, 0, 0, 0, 0, 0}
					  , {0, 0, 0, 1, 0, 0, 0}
					  , {0, 0, 0, 0, 0, 0, 0}
					  , {2, 2, 0, 0, 0, 2, 2}
					  , {2, 2, 0, 0, 0, 2, 2}
					  }; // */


	printf("><><><><><><><><><><><><\n");
	printf("  Welcome to Solitaire!\n");
	printf("><><><><><><><><><><><><\n");
	printf("Enter your moves by typing the character corresponding\nto the piece you wish to move, then typing the character\nof the place you wish to move it to.\nEnter 'q' to quit at any time.\n\n");

	int won = isWon(board);
	printf("won = %d\n", won);
	while (won != 1 && won != -1) {
		printBoard(board);
		printf("S >> ");
		scanf("%s", buffer);
		if (strcmp(buffer, "q") == 0) {
			break;
		}
		if (isValidMove(board, buffer)) {
			effectMove(board, buffer);
		} else {
			printf("Move Invalid\n");
		}
		won = isWon(board);
	}
	if (won == 1) {
		printf("A winner is you!\n");
	} else if (won == -1) {
		printf("Ya Done Son! No Moves Remaining!\n");
	} else {
		printf("Game Over, Yeah!\n");
	}
	printf("Solitaire Terminated!\n");//*/
}

// THIS IS A GIFT: Don't touch until December 25th
void printBoard(const int board[7][7]){ 
	char temp[5];
	char buf[150]; 
	char moveKey[15][100]  =
{ "    ╔═╤═╤═╗     │     ╔═╤═╤═╗    "
, " ☻  ║a│b│c║  ☻  │     ║"
, "    ╟─┼─┼─╢     │     ╟─┼─┼─╢    "
, "    ║d│e│f║     │     ║"
, "╔═╤═╃─┼─┼─╄═╤═╗ │ ╔═╤═╃─┼─┼─╄═╤═╗"
, "║g│h│i│j│k│l│m║ │ ║"
, "╟─┼─┼─┼─┼─┼─┼─╢ │ ╟─┼─┼─┼─┼─┼─┼─╢"
, "║n│o│p│x│P│O│N║ │ ║"
, "╟─┼─┼─┼─┼─┼─┼─╢ │ ╟─┼─┼─┼─┼─┼─┼─╢"
, "║M│L│K│J│I│H│G║ │ ║"
, "╚═╧═╅─┼─┼─╆═╧═╝ │ ╚═╧═╅─┼─┼─╆═╧═╝"
, "    ║F│E│D║     │     ║"
, "    ╟─┼─┼─╢     │     ╟─┼─┼─╢"
, " ☻  ║C│B│A║  ☻  │     ║"
, "    ╚═╧═╧═╝     │     ╚═╧═╧═╝"
};
	for (int i = 0; i < 15; i++) {
		strcpy(buf, moveKey[i]);
		if (i == 1 || i == 3 || i == 11 || i == 13) {
			for (int j = 2; j <= 4; j++) {
				if (board[i>>1][j] == 1) {
					strcpy(temp,"●");
				} else {
					strcpy(temp," ");
				}
				strcat(buf, temp);
				if (j < 4) {
					strcat(buf, "│");
				} else {
					strcat(buf, "║");
				}
			}
		} else if (i == 5 || i == 7 || i == 9) {
			for (int j = 0; j < 7; j++) {
				if (board[i>>1][j] == 1) {
					strcpy(temp,"●");
				} else {
					strcpy(temp," ");
				}
				strcat(buf, temp);
				if (j < 6) {
					strcat(buf, "│");
				} else {
					strcat(buf, "║");
				}
			}
		}
		printf("%s\n", buf);
	}
}
