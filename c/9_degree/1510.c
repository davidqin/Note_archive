#include <stdio.h>

int main(){
    char r[100000], ch;
    int i;

    while(1){
        i = 0;
        while(1){
            ch = getchar();
            if(ch == EOF)
                return 0;
            else if(ch == '\n'){
                r[i] = '\0';
                break;
            }
            else
                r[i++] = ch;
        }

        for(i = 0; r[i]!='\0'; i++)
            if(r[i] == ' ')
                printf("%%20");
            else
                printf("%c", r[i]);
        printf("\n");
    }
    return 0;
}
