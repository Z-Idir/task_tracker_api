#include <stdio.h>

int main(int argc, char *argv[]){
    int i = argc;

    loop:
        if (i>0){
            printf("%d\n",i);
            i--;
            goto loop;
        }
    return 0;
}