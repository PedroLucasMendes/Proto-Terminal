#include "stdio.h"
#include "string.h"

int main(){
    char num[20];
    scanf("%s",num);
    if(strcmp(num,"pedro.txt") == 0){
        printf("acertou");
    }else{
        printf("%s",num);
        printf("errou");
    }
    
    return 0;
}