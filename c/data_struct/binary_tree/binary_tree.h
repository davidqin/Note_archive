#define DATA_TYPE int

typedef struct node {
    DATA_TYPE data;
    struct node * left;
    struct node * right;
} Node;

Node * build_test_binary_tree();
Node * build_data_node(DATA_TYPE data);

void print_binary_tree(Node * head);

