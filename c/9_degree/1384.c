#include <stdio.h>
// #include <stdlib.h>

int r[1000][1000];

int main(){
    // freopen("1384.in", "r", stdin);
    int i, j, x, y, n, f;
    while(scanf("%d", &x) != -1){
        scanf("%d", &y);
        scanf("%d", &n);
        f = 0;
        for(i=0;i<x;i++)
            for(j=0;j<y;j++)
                scanf("%d", &r[i][j]);
        i = 0;
        j = y - 1;
        while(j >= 0 && i < x){
            if(n > r[i][j])
                i++;
            else if(n < r[i][j])
                j--;
            else {
                printf("Yes\n");
                f = 1;
                break;
            }
        }

        if(!f)
            printf("No\n");
    }

    return 0;
}
