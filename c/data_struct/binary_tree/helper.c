#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

Node * build_data_node(DATA_TYPE data){
    Node * node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

/*

build_test_binary_tree function return a Binary Tree Like:

              100
             /   \
            /     \
           /       \
          /         \
         /           \
        /             \
       /               \
      23               345
     /  \             /   \
   123  345          /     \
  /        \       734     62
123       4634    /   \      \
                7645  123    34
*/
Node * build_test_binary_tree(){
    Node * node_7 = build_data_node(123);
    Node * node_3 = build_data_node(123);
    node_3->left = node_7;

    Node * node_8 = build_data_node(4634);
    Node * node_4 = build_data_node(345);
    node_4->right = node_8;

    Node * node_1 = build_data_node(23);
    node_1->left = node_3;
    node_1->right = node_4;

    Node * node_9 = build_data_node(7645);
    Node * node_10 = build_data_node(2);
    Node * node_5 = build_data_node(1);
    node_5->left = node_9;
    node_5->right = node_10;

    Node * node_11 = build_data_node(34);
    Node * node_6 = build_data_node(62);
    node_6->right = node_11;

    Node * node_2 = build_data_node(345);
    node_2->left = node_5;
    node_2->right = node_6;

    Node * head = build_data_node(100);
    head->left = node_1;
    head->right = node_2;

    return head;
}

typedef enum { L_CHILD, R_CHILD, TREE_ROOT} RELATION;

typedef struct node_str {
    int width;
    int height;
    int hook;
    char * data;
} NodeStr;

#define FIRST_CHAR(x) (x[0])
#define SPACE FIRST_CHAR(" ")

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

/*

Some rules:

/ |  /  |   / |   /  |    /  |    /
1 | 12  | 123 | 1234 | 12346 | 123456

\ | \  | \   |  \   |  \    |   \
1 | 12 | 123 | 1234 | 12346 | 123456

 1  |  12  |  123  |
/ \ | /  \ | /   \ | ...

*/

int int_len(DATA_TYPE num){
    int i = 0, p;
    if(num == 0)
        return 1;

    if(num > 0){
        p = 1;
    } else {
        p = 0;
        num = -num;
    }

    while(num){
        i++;
        num /= 10;
    }

    if(p)
        return i;
    else
        return i+1;

}

void build_node_str_data(NodeStr * node){
    int i, size = node->height * (node->width + 1);
    node->data = (char*)malloc(sizeof(char) * ++size);
    memset(node->data, SPACE, size);
}

NodeStr * merge(Node * node, NodeStr * l, NodeStr * r, RELATION relation){
    NodeStr * node_str = (NodeStr*)malloc(sizeof(NodeStr));
    int node_data_width = int_len(node->data), i, j, k, n;

    if(!l && !r){
        node_str->width = node_data_width;
        node_str->height = 1;
        build_node_str_data(node_str);

        sprintf(node_str->data, "%d\n", node->data);

        if(relation == L_CHILD){
            node_str->hook = (node_str->width + 1) / 2;
        } else {
            node_str->hook = node_str->width / 2 - 1;
        }

    }

    else if(l && r){
        int f = 0;
        int differ = 0, split = 0;
        if(l->width - l->hook - 1 + r->hook < node_data_width){
            node_str->width = l->hook + 1 + node_data_width + r->width - r->hook;
            node_str->height = 2 + max(l->height, r->height);
            split = node_data_width - (l->width - l->hook - 1 + r->hook);
        } else {
            differ = l->width - l->hook - 1 + r->hook - node_data_width;
            if(differ & 1){
                differ += 1;
                split = 1;
            } else {
                differ += 2;
                split = 2;
            }

            node_str->width = split + l->width + r->width;
            node_str->height = differ / 2 + 2 + max(l->height, r->height);
        }

        build_node_str_data(node_str);

        // print Node
        for(i=0, j=0; j<(l->hook + 1 + differ / 2); j++)
            node_str->data[i * (node_str->width + 1) + j] = SPACE;
        sprintf(node_str->data + i * (node_str->width + 1) + j++, "%d", node->data);
        for(j = l->hook + 1 + differ /2 + node_data_width; j<node_str->width; j++)
            node_str->data[i * (node_str->width + 1) + j] = SPACE;
        node_str->data[i * (node_str->width + 1) + j] = '\n';

        // print '/' '\'
        for(i=1; i <= differ/2 + 1; i++){
            for(j=0; j<(l->hook + 1 + differ / 2 - i); j++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            sprintf(node_str->data + i * (node_str->width + 1) + j++, "/");
            for(k=0; k<((i-1) * 2 + node_data_width); k++, j++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            sprintf(node_str->data + i * (node_str->width + 1) + j++, "\\");
            for(; j<node_str->width; j++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
        }

        // copy l,r data
        for(k=0; k<min(r->height, l->height); k++, i++){
            for(j=0; j<(l->width); j++)
                sprintf(node_str->data + i * (node_str->width + 1) + j, "%c", *(l->data + k * (l->width + 1) + j ));
            for(n=0; n<split; j++, n++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            for(n=0; n<r->width; n++, j++)
                sprintf(node_str->data + i * (node_str->width + 1) + j, "%c", *(r->data + k * (r->width + 1) + n ));
            sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
        }

        // copy rest
        for(; i<node_str->height; i++){
            if(r->height > l->height){
                for(j=0; j<(l->width); j++)
                    node_str->data[i * (node_str->width + 1) + j] = SPACE;
                for(n=0; n<split; j++, n++)
                    node_str->data[i * (node_str->width + 1) + j] = SPACE;
                for(n=0; n<r->width; n++, j++)
                    sprintf(node_str->data + i * (node_str->width + 1) + j, "%c", *(r->data + k * (r->width + 1) + n ));
                sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
            } else {
                for(j=0; j<(l->width); j++)
                    sprintf(node_str->data + i * (node_str->width + 1) + j, "%c", *(l->data + k * (l->width + 1) + j ));
                for(n=0; n<split; j++, n++)
                    node_str->data[i * (node_str->width + 1) + j] = SPACE;
                for(n=0; n<r->width; n++, j++)
                    node_str->data[i * (node_str->width + 1) + j] = SPACE;
                sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
            }
        }

        if(relation == L_CHILD){
            node_str->hook = l->hook + 1 + differ / 2 + (node_data_width + 1) / 2;
        } else if(relation == R_CHILD) {
            node_str->hook = l->hook + 1 + differ / 2 + node_data_width / 2 - 1;
        }
    }

    else if(l){
        if(node_data_width > l->width - (l->hook + 1) ){
            node_str->width = node_data_width + l->hook + 1;
            node_str->height = l->height + 2;
        } else {
            node_str->height = l->height + l->width - (l->hook + 1) - node_data_width + 3;
            node_str->width = l->width + 1;
        }
        build_node_str_data(node_str);

        // print Node
        for(i=0, j=0; j<(node_str->width - node_data_width); j++)
            node_str->data[i * (node_str->width + 1) + j] = SPACE;
        sprintf(node_str->data + i * (node_str->width + 1) + j, "%d\n", node->data);

        // print '/'
        for(i=1; i<node_str->height - l->height; i++){

            for(j=0; j<node_str->width - node_data_width - i; j++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            sprintf(node_str->data + i * (node_str->width + 1) + j++, "/");
            for(; j<node_str->width; j++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
        }

        // copy l->data
        for(k=0; i<node_str->height; i++, k++){
            for(j=0; j<node_str->width; j++){
                if(j<l->width)
                    sprintf(node_str->data + i * (node_str->width + 1) + j, "%c", *(l->data + k * (l->width + 1) + j ));
                else
                    node_str->data[i * (node_str->width + 1) + j] = SPACE;
            }
            sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
        }

        // set hook

        if(relation == L_CHILD){
            node_str->hook = node_str->width - node_data_width + (node_data_width + 1) / 2;
        } else {
            node_str->hook = node_str->width - node_data_width + node_data_width / 2 - 1;
        }
        // for(i=0; i<(node_str->width + 1) * node_str->height; i++)
            // putchar(node_str->data[i]);

    }

    else if(r){
        if(node_data_width > r->hook){
            node_str->width = node_data_width + r->width - r->hook;
            node_str->height = r->height + 2;
        } else {
            node_str->width = r->width + 1;
            node_str->height = r->height + r->hook - node_data_width + 3;
        }

        build_node_str_data(node_str);

        // print Node
        sprintf(node_str->data, "%d", node->data);
        for(i=0, j=node_data_width; j<node_str->width; j++)
            node_str->data[i * (node_str->width + 1) + j] = SPACE;
        sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");

        // print '\'
        for(i=1; i<node_str->height - r->height; i++){

            for(j=0; j<node_data_width + i - 1; j++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            sprintf(node_str->data + i * (node_str->width + 1) + j++, "\\");
            for(; j<node_str->width; j++)
                node_str->data[i * (node_str->width + 1) + j] = SPACE;
            sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
        }

        // copy r->data
        for(k=0; i<node_str->height; i++, k++){
            for(j=0; j<node_str->width; j++){
                if(j<node_str->width - r->width)
                    node_str->data[i * (node_str->width + 1) + j] = SPACE;
                else
                    sprintf(node_str->data + i * (node_str->width + 1) + j, "%c", *(r->data + k * (r->width + 1) + j - node_str->width + r->width));
            }
            sprintf(node_str->data + i * (node_str->width + 1) + j, "\n");
        }

        // set hook
        if(relation == L_CHILD){
            node_str->hook = (node_data_width + 1) / 2;
        } else {
            node_str->hook = node_data_width / 2 - 1;
        }

        // for(i=0; i<(node_str->width + 1) * node_str->height; i++)
            // putchar(node_str->data[i]);

    }

    if(r){
        free(r->data);
        free(r);
    }

    if(l){
        free(l->data);
        free(l);
    }

    return node_str;
}

NodeStr * build_tree_str(Node * head, RELATION relation){
    if(!head)
        return NULL;

    NodeStr * l = build_tree_str(head->left, L_CHILD);
    NodeStr * r = build_tree_str(head->right, R_CHILD);
    return merge(head, l, r, relation);
}

void print_binary_tree(Node * head){
    int i;
    NodeStr * node_str = build_tree_str(head, TREE_ROOT);
    for(i=0; i<(node_str->width + 1) * node_str->height; i++)
        putchar(node_str->data[i]);
    free(node_str->data);
    free(node_str);
}
