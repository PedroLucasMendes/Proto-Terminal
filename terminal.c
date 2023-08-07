#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "funcoes.h"


int main(){
    char *entrada_usuario;
    entrada_usuario = malloc(sizeof(char)*100);
    printf(">>> ");
    while(scanf("%[^\n]%*c", entrada_usuario), strcmp(entrada_usuario, "exit") != 0){
        printf(">>> ");
        leitura_string(entrada_usuario);
    }
}