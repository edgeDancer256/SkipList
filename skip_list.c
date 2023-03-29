#include<stdio.h>
#include"skip_list.h"

int main() {
    SKIP_LIST *pl = create_skip_list();

    int choice;
    int ele;

    printf("\nPlease select an option :\n");
    printf("1. Insert elements (Will be automatically added)\n");
    printf("2. Search for an element\n");
    printf("3. Display list\n");
    printf("4. Exit\n");

    scanf("%d", &choice);

    do {
        switch(choice) {
            case 1:
                for(int i = 1; i <= 30; i++) {
                    insert_element(pl, i, i);
                }
                break;
            case 2:
                printf("Enter the element to search for : ");
                scanf("%d", &ele);
                if(search_element(pl,ele) == 1) {
                    printf("Element present in list\n");
                } else {
                    printf("Element not in list\n");
                }
                break;
            case 3:
                display_list(pl);
                break;
            case 4:
                delete_list(pl);
                return 0;
        }
        printf("\nPlease select an option :\n");
        printf("1. Insert elements (Will be automatically added)\n");
        printf("2. Search for an element\n");
        printf("3. Display list\n");
        printf("4. Exit\n");

        scanf("%d", &choice);
    }while(choice < 5);
}