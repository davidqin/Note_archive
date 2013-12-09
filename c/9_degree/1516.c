#include <stdio.h>
// #define Debug

#ifdef Debug
#include <stdlib.h>
#endif

int main(){

#ifdef Debug
    freopen("1516.in", "r", stdin);
#endif

    int i, n;
    int ns[100000];
    unsigned char f[100000], first;
    while(scanf("%d", &n) != -1){
        first = 1;
        for(i=0; i<n; i++){
            scanf("%d", ns + i);
            f[i] = 0;
            if(ns[i] & 1)
                f[i] = 1;
        }

        for(i=0; i<n; i++)
            if(f[i]){
                if(first){
                    first = 0;
                    printf("%d", ns[i]);
                } else {
                    printf(" %d", ns[i]);
                }
            }


        for(i=0; i<n; i++)
            if(!f[i]){
                if(first){
                    first = 0;
                    printf("%d", ns[i]);
                } else {
                    printf(" %d", ns[i]);
                }
            }

        printf("\n");

    }
    return 0;
}
