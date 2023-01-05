#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct node *element(struct node *dll, int i) ;
struct node *add(struct node *dll, int i, int value) ;
struct node *delete(struct node *dll, int i);

struct node {
    int value;
    struct node * next;
    struct node * prev;
};

void printNode (struct node *dll) {
    if (dll != NULL) {
        printf("< This: %p - %d - P : %p - N : %p >\n", dll, dll->value, dll->prev, dll->next);
    } else {
        printf("Null Pointer");
    }
}


void printLL (struct node *dll) {
    struct node* ptr = dll;
    printf("---\n");
    while (ptr != NULL) {
        printNode(ptr);
        ptr = ptr->next;
    }
    printf("---\n\n");
}

int main () {
 
    // Testing code! 
    struct node *dll = malloc(sizeof(struct node)); // dll is a pointer to the first item of the doubly linked list struct
    dll->value = 1;
    printLL(dll);
    printf("%d\n",element(dll, 0)->value);
    dll = add(dll, -1, 3);
    printLL(dll);
    dll = add(dll, -1, 4);
    printLL(dll);
    dll = add(dll, 1, 2);   
    printLL(dll);
    dll = add(dll, 2, 7);
    printLL(dll);
    dll = add(dll, 9, -1);
    printLL(dll);
    dll = delete(dll, 2);
    printLL(dll);
    dll = delete(dll, 0);
    printLL(dll);
    dll = delete(dll, 4);
    printLL(dll);
    dll = delete(dll, 0);
    printLL(dll);
    dll = delete(dll, 0);
    printLL(dll);
    dll = delete(dll, 0);
    printLL(dll);
    dll = delete(dll, 0);
    printLL(dll);//*/


/* Expected Output: 

---
< This: 0x1cf8590 - 1 - P : (nil) - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8590 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8590 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf85f0 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf8610 >
< This: 0x1cf8610 - 7 - P : 0x1cf85f0 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8610 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf85f0 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---
*/
}


struct node *element(struct node *dll, int i) {
    struct node* ptr = dll; // ptr and dll point to the same adress, which is the addy to the doubly linked list from main, ptr can be manipulated
    int index = 0;
    while (ptr != NULL) {
        if (index == i) {
            break;
        }
        ptr = ptr->next;
        index++; 
    }
    return ptr;
}

struct node *add(struct node *dll, int i, int value) {
    struct node* ptr = dll;
    struct node* ptr2 = dll;
    int sizeofdll = 0;
    while(ptr2 != NULL) {
        sizeofdll++;
        ptr2 = ptr2->next;
    }
    
    if ((i < 0) || (i >= sizeofdll)) {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = malloc(sizeof(struct node));
        ptr->next->value = value;
        ptr->next->next = NULL;
        ptr->next->prev = ptr;
        return dll;
    } else if (i == 0) {
        struct node* newinsert = malloc(sizeof(struct node));
        newinsert->value = value;
        newinsert->next = ptr;
        newinsert->prev = NULL;
        ptr->prev = newinsert;
        return newinsert;
    } else {
        int index = 0;
        struct node* prevptr;
        while (ptr != NULL) {
            if (index == i) {
                break;
            }
            prevptr = ptr;
            ptr = ptr->next;
            index++; 
        }
        prevptr->next = malloc(sizeof(struct node));
        prevptr->next->next = ptr;
        prevptr->next->value = value;
        prevptr->next->prev = prevptr;
        ptr->prev = prevptr -> next;
        return dll;
    }
}

struct node *delete(struct node *dll, int i) {
    struct node* ptr = dll;
    struct node* ptr2 = dll;
    struct node* newnode;
    int sizeofdll = 0;
    while(ptr2 != NULL) {
        sizeofdll++;
        ptr2 = ptr2->next;
    }
    if (i == 0) {
        if (sizeofdll == 1) {
            free(ptr);
            return NULL;
        } else {
            newnode = ptr->next;
            ptr->next->prev = NULL;
            free(ptr);
            return newnode;
        }
    } else {
        int index = 0;
        struct node* prevptr;
        while (ptr != NULL) {
            if (index == i) {
                break;
            }
            prevptr = ptr;
            ptr = ptr->next;
            index++; 
        }
        if (ptr == NULL) {
            return dll;
        } else if (ptr -> next == NULL) {
            prevptr->next = NULL;
        } else {
            prevptr->next = ptr->next;
            ptr->next->prev = prevptr;
        }
        free(ptr);
        return dll;

    } 
}
