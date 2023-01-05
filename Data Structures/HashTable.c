#include <stdio.h>
#include <stdlib.h>

struct sll {
     int key;
     int val;
     struct sll* next;
};

typedef struct sll SLL;

struct hTable {
	int size;
    struct sll** arr;    
};

typedef struct hTable HashTable;

int hash(int key, int size);
HashTable* init (int size);
int walkSLL(SLL* cur, int key);
int lookup(HashTable* table, int key);
void insert(HashTable* table, int key, int val);


HashTable* init (int size) {
	HashTable * h = malloc(sizeof(HashTable));
	h->size = size;
	SLL ** x = malloc(sizeof(SLL*)*size);
	for (int i = 0; i < size; i++) {
		x[i] = NULL;
	}
	h->arr = x;
	return h;
}

int hash(int key, int size) {
	return (777*key%size);
}

void insert(HashTable* table, int key, int val) {
	int index = hash(key, table->size);
	SLL * s = malloc(sizeof(SLL));
	s->key = key;
	s->val = val;
	s->next = table->arr[index];
	table->arr[index] = s;
}

int walkSLL(SLL* cur, int key) {
	SLL * currentpos = cur;
	if (currentpos->key == key) {
			return (currentpos->val);
	}
	currentpos = currentpos->next;
	while (currentpos != NULL) {
		if (currentpos->key == key) {
			return (currentpos->val);
		}
		currentpos = currentpos->next;
	} 
	return -1;
}

int lookup(HashTable* table, int key) {
	int index = hash(key, table->size);
	printf("index: %d\n", index);

	if ((index > (table->size-1)) || (index < 0)) {
		return -1;
	}
	if (table->arr[index] == NULL) {
		return -1;
	}

	SLL * currentpos = table->arr[index];
	if (currentpos->key == key) {
			return (currentpos->val);
	}
	currentpos = currentpos->next;
	while (currentpos != NULL) {
		if (currentpos->key == key) {
			return (currentpos->val);
		}
		currentpos = currentpos->next;
	} 
	return -1;
}

void printSLL(SLL* node) {
	printf("( %d : %d ) ", node->key, node->val);
	if (node->next != NULL) {
		printf(", ");
		printSLL(node->next);
	} else {
		printf("\n");
	}
}

void printTable (HashTable* table) {
	printf("---table at %p--------------\n", table);
	for (int i = 0; i < table->size; i++) {
		printf("%d -> ", i);
		if (table->arr[i] != NULL) {
			printSLL(table->arr[i]);
		} else {
			printf("X\n");
		}
	}
}

int main() {
	int n1 = 4;
	HashTable* table1 = init(n1);
	
	insert(table1, 55, 123);
	insert(table1, 98, 456);
	insert(table1, 2, 789);		
	
	printTable(table1);
	//printf("%d\n",walkSLL(table2->arr[3], 24));

/* expected output:

---table at 0x556d326cc2a0--------------
0 -> X
1 -> X
2 -> ( 2 : 789 ) , ( 98 : 456 ) 
3 -> ( 55 : 123 ) 

*/

// test case 2
    int n2 = 11;
    HashTable* table2 = init(n2);
    
    for (int i = 1; i < 4; i ++) {
        insert(table2, i, i*3);
        insert(table2, i*8, i*24);
    }
    printTable(table2);
	printf("%d\n",lookup(table2, 16));
    
/* expected output: 

---table at 0x55db8ecfb2a0--------------
0 -> X
1 -> ( 8 : 24 ) 
2 -> ( 16 : 48 ) 
3 -> ( 24 : 72 ) , ( 2 : 6 ) 
4 -> X
5 -> X
6 -> X
7 -> ( 1 : 3 ) 
8 -> X
9 -> X
10 -> ( 3 : 9 ) 

*/

    /*int n3 = 34;
    HashTable* table3 = init(n3);
    
    for (int i = 1; i < 100; i ++) {
        insert(table3, i, i*3);
        insert(table3, i*8, i*24);
    }
    printTable(table3);*/
    
    
/* expected output:

---table at 0x556bd1d9e8a0--------------
0 -> ( 680 : 2040 ) , ( 544 : 1632 ) , ( 68 : 204 ) , ( 408 : 1224 ) , ( 272 : 816 ) , ( 34 : 102 ) , ( 136 : 408 ) 
1 -> ( 95 : 285 ) , ( 61 : 183 ) , ( 27 : 81 ) 
2 -> ( 768 : 2304 ) , ( 88 : 264 ) , ( 632 : 1896 ) , ( 496 : 1488 ) , ( 54 : 162 ) , ( 360 : 1080 ) , ( 224 : 672 ) , ( 20 : 60 ) , ( 88 : 264 ) 
3 -> ( 81 : 243 ) , ( 47 : 141 ) , ( 13 : 39 ) 
4 -> ( 720 : 2160 ) , ( 74 : 222 ) , ( 584 : 1752 ) , ( 448 : 1344 ) , ( 40 : 120 ) , ( 312 : 936 ) , ( 176 : 528 ) , ( 6 : 18 ) , ( 40 : 120 ) 
5 -> ( 67 : 201 ) , ( 33 : 99 ) 
6 -> ( 94 : 282 ) , ( 672 : 2016 ) , ( 536 : 1608 ) , ( 60 : 180 ) , ( 400 : 1200 ) , ( 264 : 792 ) , ( 26 : 78 ) , ( 128 : 384 ) 
7 -> ( 87 : 261 ) , ( 53 : 159 ) , ( 19 : 57 ) 
8 -> ( 760 : 2280 ) , ( 80 : 240 ) , ( 624 : 1872 ) , ( 488 : 1464 ) , ( 46 : 138 ) , ( 352 : 1056 ) , ( 216 : 648 ) , ( 12 : 36 ) , ( 80 : 240 ) 
9 -> ( 73 : 219 ) , ( 39 : 117 ) , ( 5 : 15 ) 
10 -> ( 712 : 2136 ) , ( 576 : 1728 ) , ( 66 : 198 ) , ( 440 : 1320 ) , ( 304 : 912 ) , ( 32 : 96 ) , ( 168 : 504 ) , ( 32 : 96 ) 
11 -> ( 93 : 279 ) , ( 59 : 177 ) , ( 25 : 75 ) 
12 -> ( 86 : 258 ) , ( 664 : 1992 ) , ( 528 : 1584 ) , ( 52 : 156 ) , ( 392 : 1176 ) , ( 256 : 768 ) , ( 18 : 54 ) , ( 120 : 360 ) 
13 -> ( 79 : 237 ) , ( 45 : 135 ) , ( 11 : 33 ) 
14 -> ( 752 : 2256 ) , ( 616 : 1848 ) , ( 72 : 216 ) , ( 480 : 1440 ) , ( 344 : 1032 ) , ( 38 : 114 ) , ( 208 : 624 ) , ( 72 : 216 ) , ( 4 : 12 ) 
15 -> ( 99 : 297 ) , ( 65 : 195 ) , ( 31 : 93 ) 
16 -> ( 92 : 276 ) , ( 704 : 2112 ) , ( 568 : 1704 ) , ( 58 : 174 ) , ( 432 : 1296 ) , ( 296 : 888 ) , ( 24 : 72 ) , ( 160 : 480 ) , ( 24 : 72 ) 
17 -> ( 85 : 255 ) , ( 51 : 153 ) , ( 17 : 51 ) 
18 -> ( 792 : 2376 ) , ( 656 : 1968 ) , ( 78 : 234 ) , ( 520 : 1560 ) , ( 384 : 1152 ) , ( 44 : 132 ) , ( 248 : 744 ) , ( 112 : 336 ) , ( 10 : 30 ) 
19 -> ( 71 : 213 ) , ( 37 : 111 ) , ( 3 : 9 ) 
20 -> ( 98 : 294 ) , ( 744 : 2232 ) , ( 608 : 1824 ) , ( 64 : 192 ) , ( 472 : 1416 ) , ( 336 : 1008 ) , ( 30 : 90 ) , ( 200 : 600 ) , ( 64 : 192 ) 
21 -> ( 91 : 273 ) , ( 57 : 171 ) , ( 23 : 69 ) 
22 -> ( 696 : 2088 ) , ( 84 : 252 ) , ( 560 : 1680 ) , ( 424 : 1272 ) , ( 50 : 150 ) , ( 288 : 864 ) , ( 152 : 456 ) , ( 16 : 48 ) , ( 16 : 48 ) 
23 -> ( 77 : 231 ) , ( 43 : 129 ) , ( 9 : 27 ) 
24 -> ( 784 : 2352 ) , ( 648 : 1944 ) , ( 70 : 210 ) , ( 512 : 1536 ) , ( 376 : 1128 ) , ( 36 : 108 ) , ( 240 : 720 ) , ( 104 : 312 ) , ( 2 : 6 ) 
25 -> ( 97 : 291 ) , ( 63 : 189 ) , ( 29 : 87 ) 
26 -> ( 736 : 2208 ) , ( 90 : 270 ) , ( 600 : 1800 ) , ( 464 : 1392 ) , ( 56 : 168 ) , ( 328 : 984 ) , ( 192 : 576 ) , ( 22 : 66 ) , ( 56 : 168 ) 
27 -> ( 83 : 249 ) , ( 49 : 147 ) , ( 15 : 45 ) 
28 -> ( 688 : 2064 ) , ( 76 : 228 ) , ( 552 : 1656 ) , ( 416 : 1248 ) , ( 42 : 126 ) , ( 280 : 840 ) , ( 144 : 432 ) , ( 8 : 24 ) , ( 8 : 24 ) 
29 -> ( 69 : 207 ) , ( 35 : 105 ) , ( 1 : 3 ) 
30 -> ( 776 : 2328 ) , ( 96 : 288 ) , ( 640 : 1920 ) , ( 504 : 1512 ) , ( 62 : 186 ) , ( 368 : 1104 ) , ( 232 : 696 ) , ( 28 : 84 ) , ( 96 : 288 ) 
31 -> ( 89 : 267 ) , ( 55 : 165 ) , ( 21 : 63 ) 
32 -> ( 728 : 2184 ) , ( 82 : 246 ) , ( 592 : 1776 ) , ( 456 : 1368 ) , ( 48 : 144 ) , ( 320 : 960 ) , ( 184 : 552 ) , ( 14 : 42 ) , ( 48 : 144 ) 
33 -> ( 75 : 225 ) , ( 41 : 123 ) , ( 7 : 21 ) 

*/
}
