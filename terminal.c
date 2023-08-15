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
        int cont = leitura_string(GetPrograma(program_args));
        if(cont == 1){
            ls();
        }else if(cont == 2){
            cd(GetArgs(program_args));
        }else if(cont == 3){
            pwd();
        }else{
            
        }
        
        printf(">>> ");
    }
}