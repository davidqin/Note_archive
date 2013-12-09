#include <stdio.h>
long int r[71];

void init_r(){
    int i;
    r[0] = 0;
    r[1] = 1;
    r[2] = 2;
    for(i=3; i<71; i++){
        r[i] = r[i-1];
        r[i] += r[i-2];
    }
}

int main(){
    int n;
    init_r();
    while(scanf("%d", &n) != -1){
        printf("%ld\n", r[n]);
    }
    return 0;
}
