#include <stdio.h>

int r[1500] = {1};
int p = 1;

int get_min(int a, int b, int c){
    int m;
    m = a < b ? a : b;
    m = m < c ? m : c;
    return m;
}

void dirty_number(){
    int p2 = 0, p3 = 0, p5 = 0, n = 0;
    while(p < 1500){
        r[p++] = get_min(r[p2] * 2, r[p3] * 3, r[p5] * 5);
        while(r[p2] * 2 <= r[p-1])++p2;
        while(r[p3] * 3 <= r[p-1])++p3;
        while(r[p5] * 5 <= r[p-1])++p5;

    }
    // for(int i=0;i<1500;i++)
        // printf("%d,\n", r[i], i);

}


int main(){
    dirty_number();

    int n;
    while(scanf("%d", &n) != -1)
        printf("%d", r[n-1]);

    return 0;
}
