#include <stdio.h>
#include <stdlib.h>

int n;

typedef struct node
{
    struct node * l;
    struct node * r;
    int d;
} Node;

Node * b_N(int d){
    Node * h = (Node*)malloc(sizeof(Node));
    h->d = d;
    h->l = NULL;
    h->r = NULL;
    return h;
}

int get_index(int m_r[], int d){
    int i;
    for(i=0; i<n; i++){
        if(m_r[i] == d)
            return i;
    }
    return -1;
}

void free_T(Node * head){
    if(!head)
        return;

    free_T(head->l);
    free_T(head->r);
    free(head);
}

Node * b_T(int f_r[], int m_r[], int l){
    int head = f_r[0];
    Node * h = b_N(head);

    int h_index = get_index(m_r, head);

    if(h_index == -1) {
        free(h);
        return NULL;
    }

    if(h_index == 0){
        h->l = NULL;
    } else {
        h->l = b_T(f_r + 1, m_r, h_index);
        if(!h->l){
            free_T(h);
            return NULL;
        }
    }

    if(h_index == l - 1){
        h->r = NULL;
    } else {
        h->r = b_T(f_r + 1 + h_index, m_r + h_index + 1, l - h_index - 1);
        if(!h->r){
            free_T(h);
            return NULL;
        }
    }

    if(!h->l && !h->r && l != 1){
        free(h);
        h = NULL;
    }

    return h;
}

void p_a_r(Node * head){
    if(!head)
        return;

    p_a_r(head->l);
    p_a_r(head->r);
    printf("%d ", head->d);
    free(head);
}

int main(){
    // freopen("1385.in",  "r", stdin);
    int i;
    int f_r[1005], m_r[1005];
    Node * h;
    while(scanf("%d", &n) != -1){
        for(i=0; i<n; i++) scanf("%d", f_r + i);
        for(i=0; i<n; i++) scanf("%d", m_r + i);

        h = b_T(f_r, m_r, n);

        if(!h){
            printf("No\n");
            continue;
        }
        p_a_r(h);
        printf("\n");
    }
    return 0;
}
