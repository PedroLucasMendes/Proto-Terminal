#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "funcoes.h"
#include "parser.h"

int main(){
    char entrada_usuario[100];
    printf(">>> ");
    while(scanf("%[^\n]%*c", entrada_usuario), strcmp(entrada_usuario, "exit") != 0){
        entrada_t *program_args = quebra_entrada(entrada_usuario);
        printa_struct(program_args);
        printf(">>> ");
    }
}