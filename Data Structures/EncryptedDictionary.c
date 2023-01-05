/* 
Encrypted-Key Dictionaries 
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct slot {
	int n;
	int *values;
	int key;
} Slot;

typedef struct edict {
	Slot * slots;	
	int n;
	int (*encrypt)(int j); // pointer to a function that accepts an integer and returns an integer
} Edict;

void printEntry (Slot* entry) {
	printf("| |--- Encrypted Value = %d ---\n", entry->key);
	printf("| | Number of Values = %d\n", entry->n);
	printf("| | ");
	for (int i = 0; i < entry->n; i++) {
		printf("%d  ", entry->values[i]);
	}
	printf("\n| |---------------------\n| \n");
}

void printEdict (Edict* t) {
	printf("----------------------\n");
	printf("| No. of Entries: %d\n| \n", t->n);
	for (int i = 0; i < t->n; i++) {
		printEntry(&(t->slots[i]));	// passing the address of slots[i]
	}
	printf("----------------------\n\n");
}

int cypher1 (int n) {
	return (8*n*n - 21*n + 18) % 8;
}

int cypher2 (int n) {
	return ((n - 4)*(n + 12)*(n * 3)) % 8;
}

Edict * createEdict(int (*func)(int j)) {
	Edict * temp = malloc(sizeof(Edict));
	temp->n = 0;
	temp->slots = NULL;
	temp->encrypt = func;
	return temp;
}

int insertValue(Edict*d, int val) {
	if (d == NULL) {
		return -1;
	}
	if (d->slots == NULL) { // if slots is null then we allocate memory to make an array that will store an instance of the slot struct (not a pointer to it)
		Slot * s = malloc(sizeof(Slot)); // makes a pointer s that points to an instance of the struct Slot with all the values
		s->key = d->encrypt(val);
		s->n = 1;
		s->values = malloc(sizeof(int));
		s->values[0] = val;
		d->slots = malloc(sizeof(Slot)); // allocating memory in the slots to hold an instance of a slot, not taking pointers to slot structs, actual structs.
		d->slots[0] = *s; // *s is the actual struct while s is the pointer to the struct
		d->n = 1;
	} else {
		int found = 0;
		int index = 0;
		for (int i = 0; i < (d->n); i++) { // checks to see if the encrypted key is already in the edict or not
			if ((d->slots[i]).key == d->encrypt(val)) {
				found = 1;
				index = i;
				break;
			}
			
		}
		if (found) { // will add the value to the specific slot if the key is found
			(d->slots[index]).n += 1;
			(d->slots[index]).values = realloc((d->slots[index]).values, sizeof(int)*((d->slots[index]).n));
			(d->slots[index]).values[((d->slots[index]).n) - 1] = val;
		} else { // if not found then it will make a slot instance and add it to the slots array by reallocating memory
			d->n += 1;
			d->slots = realloc(d->slots, sizeof(Slot)*(d->n));
			Slot * s = malloc(sizeof(Slot));
			s->n = 1;
			s->key = d->encrypt(val);
			s->values = malloc(sizeof(int));
			s->values[0] = val;
			d->slots[(d->n)-1] = *s;
		}
	}
	return 0;
}

void destroyEdict(Edict * d) {
	for (int i = 0; i < (d->n); i++) {
		free((d->slots[i]).values);
	}
	free(d->slots);
	free(d);
}

int main () {
	Edict* t = createEdict(&cypher1);
	printEdict(t);
	//2400
	for (int i = 2360; i < 2400; i++) {
		if (insertValue(t, i) == -1) {
			break;
		}
	}
	printEdict(t);
	destroyEdict(t);
}



/* Expected Output 

----------------------
| No. of Entries: 0
| 
----------------------

----------------------
| No. of Entries: 8
| 
| |--- Encrypted Value = 2 ---
| | Number of Values = 5
| | 2360  2368  2376  2384  2392  
| |---------------------
| 
| |--- Encrypted Value = 5 ---
| | Number of Values = 5
| | 2361  2369  2377  2385  2393  
| |---------------------
| 
| |--- Encrypted Value = 0 ---
| | Number of Values = 5
| | 2362  2370  2378  2386  2394  
| |---------------------
| 
| |--- Encrypted Value = 3 ---
| | Number of Values = 5
| | 2363  2371  2379  2387  2395  
| |---------------------
| 
| |--- Encrypted Value = 6 ---
| | Number of Values = 5
| | 2364  2372  2380  2388  2396  
| |---------------------
| 
| |--- Encrypted Value = 1 ---
| | Number of Values = 5
| | 2365  2373  2381  2389  2397  
| |---------------------
| 
| |--- Encrypted Value = 4 ---
| | Number of Values = 5
| | 2366  2374  2382  2390  2398  
| |---------------------
| 
| |--- Encrypted Value = 7 ---
| | Number of Values = 5
| | 2367  2375  2383  2391  2399  
| |---------------------
| 
----------------------


*/
