#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include 'funcoes.h'

int main(){
    char *entrada_usuario;
    entrada_usuario = malloc(sizeof(char)*100);
    while(strcmp(entrada_usuario, "exit") != 0){
        printf(">>> ");
        scanf("%s", entrada_usuario);  
        //int comando = fork();
     aa   //printf("%d\n",comando);
    }
}