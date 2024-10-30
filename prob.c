#include <stdio.h>
#include <string.h>

int main(){
    int a=1;
    int b=2;
    int temp=a;
    a =b;
    b=a;
    printf("%d, %d", a, b);
    return 0;
}

