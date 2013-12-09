#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int d;
    struct node * n;
} Node;

Node * c_N(int d){
    Node * n = (Node*)malloc(sizeof(Node));
    n->n = NULL;
    n->d = d;
    return n;
}

Node * r_L(Node * h){
    Node * p, * n;
    p = h;
    h = h->n;
    p->n = NULL;
    if(!h)
        return p;

    while(h){
        n = h->n;
        h->n=p;
        p = h;
        h = n;
    }
    return p;
}

void p_L(Node * h){
    Node * p;
    if(h){
        printf("%d", h->d);
        p = h;
        h = h->n;
        free(p);
    }
    while(h){
        printf(" %d", h->d);
        p = h;
        h = h->n;
        free(p);
    }
    printf("\n");
}

int main(){
    // freopen("1518.in", "r", stdin);
    int i, n, d;
    Node * h, * t;
    while(scanf("%d", &n) != EOF){
        if(n == 0){
            printf("NULL\n");
            continue;
        }
        for(i=0; i < n; i++){
            scanf("%d", &d);
            if(!i){
                h = c_N(d);
                t = h;
            } else {
                t->n = c_N(d);
                t = t->n;
            }
        }

        h = r_L(h);
        p_L(h);
    }
    return 0;
}
