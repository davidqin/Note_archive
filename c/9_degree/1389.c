#include <stdio.h>
int main(){
    int n;
    long long i = 1;
    while(scanf("%d", &n) != -1){
        printf("%lld\n", (i << n - 1));
    }
    return 0;
}
