#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/******************The binary tree***********************
 * The following is an illustration of the binary tree
 * I *highly* recommend you test your algorithm on.
 ********************************************************
 *                        Nicholas
 *                        /      \
 *                     Mark      Parker
 *                    /          /     \
 *                Swaleh     Soroush   Other Mark
 *                                 \
 *                                 Ana
 *                                 /
 *                             Bassel
 *
 *
 * (where "/" indicates a left branch, 
 *    and "\" indicates a right branch)
 *
 */ 

typedef struct node {
    char * name;
    char * tea;
    struct node * left;
    struct node * right;
} Node;

int depth(Node *root) ;
int dfs(Node *root, char * name) ;

int sizeoftree(Node *root) {
    if (root == NULL) {
        return 0;
    } else {
        return (1 + sizeoftree(root->left) + sizeoftree(root->right));
    }
}

int main() {
    // Testing code ^_^
    Node *root = malloc(sizeof(Node));
    root->name = "Nicholas";
    root->tea = "Orange Pekoe with Lemon";
    root->left = malloc(sizeof(Node));
    root->left->left = malloc(sizeof(Node));
    root->left->right = NULL;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->right = malloc(sizeof(Node));
    root->right->left = malloc(sizeof(Node));
    root->right->right = malloc(sizeof(Node));

    /*root->right->right->left = malloc(sizeof(Node));
    root->right->right->left->name = "deez";
    root->right->right->left->tea = "nuts";
    root->right->right->left->right = NULL;
    root->right->right->left->left = NULL;//*/

    root->right->right->right = NULL;
    root->right->left->left = NULL;
    root->right->left->right = malloc(sizeof(Node));
    root->right->left->right->left = malloc(sizeof(Node));
    root->right->left->right->right = NULL;
    root->right->left->right->left->left = NULL;
    root->right->left->right->left->right = NULL;
    
    root->left->name = "Mark";
    root->left->tea = "Green";
    
    root->right->left->name = "Soroush";
    root->right->left->tea = "Oolong";
    
    root->right->name = "Parker";
    root->right->tea = "Rooibos";
    
    root->right->right->name = "Other Mark";
    root->right->right->tea = "Sencha";
    
    root->left->left->name = "Swaleh";
    root->left->left->tea = "White";
    
    root->right->left->right->name = "Ana";
    root->right->left->right->tea = "Hibiscus";
    
    root->right->left->right->left->name = "Bassel";
    root->right->left->right->left->tea = "Matcha";
    
    printf("The depth of the tree is: %d\n", depth(root));
    // expected result is 5.
    
    printf("Depth First Search for : Nicholas\n");
    printf("result: %d\n", dfs(root, "Nicholas"));
    // expected result is 1
    
    printf("Depth First Search for : Other Mark\n");
    printf("result: %d\n", dfs(root, "Other Mark"));
    // expected result is 8
    
    printf("Depth First Search for : Parker\n");
    printf("result: %d\n", dfs(root, "Parker"));
    // expected result is 4
    
    printf("Depth First Search for : Julius Ceasar\n");
    printf("result: %d\n", dfs(root, "Julius Ceasar"));
    // expected result is -1
    char * name = "Mark";
    printf("Depth First Search for : %s\n", name);
    printf("result: %d\n", dfs(root, name));//*/

    free(root->right->left->right->left);
    free(root->right->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->right);
    free(root->left->left);
    free(root->left);
    free(root);//*/
}

int depth(Node * root) {
    if (root == NULL) {
        return 0;
    } else {
        int depthleft = depth(root->left);
        int depthright = depth(root->right);

        if (depthleft > depthright) {
            return depthleft + 1;
        } else {
            return depthright + 1;
        }
    }
}

int dfs(Node *root, char * name) {
    static int found = 0, counter = 0, iteration = 0;
    int size = -1;
    static char * toprootname;

    if (iteration == 0) {
        toprootname = root->name;
        size = sizeoftree(root);
    }

    if (root == NULL) {
        return 0;
    } else {
        counter++;
        iteration++;
    }
    // if the search is on the first node then its not good
    if (strcmp(root->name, name) == 0) {
        // if statement to see if the first node was the correct one, if it is then it should run a certain set of instrucitons compared to if its a further down node
        if (iteration == 1) {
            iteration = 0;
            counter = 0;
            return 1;
        } else {
            found = 1;
            iteration = 0;
            return 1;
        }
    } 
    
    if (!found) {
    int left = dfs(root->left, name);
    }
    if (!found) {
    int right = dfs(root->right, name);
    }

    if ((counter == size) && (!found)) {
        counter = 0;
        return -1;
    }

    if (strcmp(toprootname, root->name) == 0) {
        found = 0;
        int temp = counter;
        counter = 0;
        return temp;
    }

    return counter;

    //return -1;

}// */

/*int dfs(Node *root, char * name) {
    int nodesChecked = 0;
    
    static int found = 0, iteration = 0 counter = 0;
    int size = -1;
    static char * toprootname;

    if (iteration == 0) {
        size = sizeoftree(root);
        toprootname = root->name;
        //printf("size of tree: %d, top root name: %s\n", size, toprootname);
    }

    if (root == NULL) {
        return nodesChecked;
    } else {
        counter++;
        iteration++;
    }

    if (strcmp(root->name, name) == 0) {
        found = 1;
        iteration = 0;
        return 1;
    }

    nodesChecked++;

    nodesChecked += dfs(root->left, name);
    nodesChecked += dfs(root->right, name);
    //printf("%s: nodeschecked: %d , size: %d\n, found: %d\n", root->name, nodesChecked, size, found);

    if ((nodesChecked == size) && (!found)) {
        return -1;
    }

    if (strcmp(toprootname, root->name) == 0) {
        found = 0;
        return nodesChecked;
    }

    return nodesChecked;

}//*/

/*int dfs(Node *root, char * name) {
    int nodesChecked = 0;


    if (root == NULL) {
        return nodesChecked;
    }

    if (strcmp(root->name, name) == 0) {
        return 1;
    }

    nodesChecked++;
    nodesChecked += dfs(root->left, name);
    nodesChecked += dfs(root->right, name);

    //printf("%s: nodeschecked: %d , size: %d\n, found: %d\n", root->name, nodesChecked, size, found);

    return nodesChecked;

}//*/



