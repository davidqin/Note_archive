#include <stdio.h>

int main(){
    int n, s, i, num;
    scanf("%d", &num);
    while(num--){
        scanf("%d", &n);
        s = 0;
        i = 0;
        while(n && i++ < sizeof(int) * 8){
            s += n & 1;
            n = n >> 1;
        }
        printf("%d\n", s);
    }
    return 0;
}
