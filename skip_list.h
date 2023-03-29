typedef struct node {
    /* data */
    int info;
    int level;
    int key;
    struct node **next;
}NODE;

typedef struct skip_list {
    int level;
    NODE *head;
}SKIP_LIST;

NODE* create_node(int value, int key, int level);
SKIP_LIST* create_skip_list();
void insert_element(SKIP_LIST *pl, int key, int info);
int search_element(SKIP_LIST *pl, int key);
void display_list(SKIP_LIST *pl);
void delete_list(SKIP_LIST *pl);
int randomlevel();

void destroy_node(NODE *p);

int delete_element(SKIP_LIST *pl, int key);
