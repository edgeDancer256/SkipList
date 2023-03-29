#include<stdio.h>
#include"skip_list.h"

int main() {
    SKIP_LIST *pl = create_skip_list();

    int choice;

    printf("Please select an option :\n");
    printf("1. Insert elements (Will be automatically added)\n");
    printf("2. Search for an element\n");
    printf("3. Display list\n");

    scanf("%d", &choice);

    switch(choice) {
        case 1:
            for(int i = 1; i <= 30; i++) {
                insert_element(pl, i, i);
            }
    }

    insert_element(pl, 3, 3);
    insert_element(pl, 1, 1);
    insert_element(pl, 2, 2);
    insert_element(pl, 5, 5);
    insert_element(pl, 4, 4);

    insert_element(pl, 7, 7);
    insert_element(pl, 8, 8);
    insert_element(pl, 6, 6);
    insert_element(pl, 9, 9);
    insert_element(pl, 10, 10);

    insert_element(pl, 11, 11);
    insert_element(pl, 12, 12);
    insert_element(pl, 13, 13);
    insert_element(pl, 14, 14);
    insert_element(pl, 15, 15);

    display_list(pl);

    if(search_element(pl,10) == 1) {
        printf("Element found\n");
    } else {
        printf("Element not found\n");
    }

    if(search_element(pl,20) == 1) {
        printf("Element found\n");
    } else {
        printf("Element not found\n");
    }


    delete_list(pl);

    return 0;
}