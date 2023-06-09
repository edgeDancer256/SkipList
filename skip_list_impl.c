#include<stdio.h>
#include<stdlib.h>
#include"skip_list.h"

#define SKIPLIST_MAX_LEVEL 8
#define MAX_INT 100000

/*Function to allocate memory to and initialise a NODE*/
NODE* create_node(int info, int key, int level) {
    NODE* new_node = (NODE *)malloc(sizeof(NODE));

    if(new_node == NULL) {      //Throw error if memory allocation went wrong
        fprintf(stderr, "Error during memory allocation\n");
        exit(EXIT_FAILURE);
    }
    //Assign corresponding values for each variable and set the next fields to NULL
    new_node->info = info;
    new_node->key = key;
    new_node->level = level;
    new_node->next = calloc(level+1, sizeof(NODE*));

    if(new_node->next == NULL) {//Throw error if memory allocation went wrong
        fprintf(stderr, "Error during memory allocation\n");
        exit(EXIT_FAILURE);
    }
    //Return the newly created node
    return new_node;
}


/*Function to initialise a skiplist
Return a skiplist when successfully created*/
SKIP_LIST* create_skip_list() {
    SKIP_LIST* sk_list = (SKIP_LIST*)malloc(sizeof(SKIP_LIST));

    if(sk_list == NULL) {
        fprintf(stderr, "Error during memory allocation\n");
        exit(EXIT_FAILURE);
    }

    //Creating a root NODE under presumption that '0' is not allowed in the skiplist elements
    sk_list->head = create_node(0, MAX_INT, SKIPLIST_MAX_LEVEL); 
    sk_list->level = 0;
    //Return the newly created SkipList
    return sk_list;
}

/*Function to insert an element into the skiplist
Takes the list pointer, key, info and level as arguments*/
void insert_element(SKIP_LIST *pl, int key, int info) {
    int i;
    NODE* curr;
    NODE* update[SKIPLIST_MAX_LEVEL+1];

    curr = pl->head;
    //Traverse the list till we reach the position to insert the element
    for(i = pl->level; i >= 0; i--) {
        while(curr->next[i] != NULL && curr->next[i]->key < key) {
            curr = curr->next[i];
        }
        update[i] = curr;   //Store the predecessor for nodes of the route traversed
    }

    curr = curr->next[0];
    //If only info is being updated....do that and return
    if(curr != NULL && curr->key == key) {
        curr->info = info;
        return;
    } else {
        //Get a random level for insertion, update the previous links appropriately
        int newlevel = randomlevel(); //Initialise random level
        if(newlevel > pl->level) { //if newlevel > level of skiplist, update all head pointers
            for(i = pl->level+1; i <= newlevel+1; i++) {
                update[i] = pl->head;
            }
            pl->level = newlevel;
        }
        //Creating a new NODE with given parameters
        curr = create_node(info, key, newlevel);
        //Updating pointers on all levels required
        for(i = 0; i <= newlevel; i++) {
            curr->next[i] = update[i]->next[i];
            update[i]->next[i] = curr;
        }
    }
}

/*Function to search for an element in the list
Takes a pointer to the list and the search key as arguments*/
int search_element(SKIP_LIST *pl, int key) {
    int i;
    NODE* curr = pl->head;
    //Traverse the list until we find the element, or reach the end of the list 
    for(i = pl->level; i >= 0; i--) {
        while(curr->next[i] != NULL && curr->next[i]->key < key) {
            curr = curr->next[i];
        }
    }
    curr = curr->next[0];
    if(curr != NULL && curr->key == key) { //if search successful, return 1
        return 1;
    } else { //if search unsuccessful, return 0
        return 0;
    }
}

/*Function to display the list level wise*/
void display_list(SKIP_LIST *pl) {
    NODE *temp = pl->head;
    //Traverse the list level wise.
    //Display all elements on that level
    for(int i = pl->level; i >= 0; i--) {
        NODE *n = temp->next[i];
        printf("Level:%d : ", i);
        while(n != NULL) {
            printf("%d -> ", n->info);
            n = n->next[i];
        }
        printf("NULL");
        printf("\n");
    }
}


/*Function to generate level for a new node*/
int randomlevel() {
    int level = 0;
    //We can increase the level as long as it is not greater than the maximum allowed level
    while(rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL) { 
        level++;
    }

    return level;
}

/*Function to destroy the skiplist*/
void delete_list(SKIP_LIST *pl) {
    NODE *temp1, *temp2;
    temp1 = pl->head;
    while(temp1 != NULL) {
        temp2 = temp1;
        temp1 = temp1->next[0];
        destroy_node(temp2);
    }
    free(pl);
}

/*Function to destroy a node*/
void destroy_node(NODE *p) {
    if(p != NULL) {
        free(p->next);
        free(p);
    }
}
