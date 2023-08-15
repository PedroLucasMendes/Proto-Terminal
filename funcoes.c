#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
este arquivo contem as funcoes que serao chamadas no arquivo terminal.c
*/
void ls(){
    printf("listando arquivos:\n");
}

void cd(){


    printf("mudando para diretorio escolhido:\n");
}


void pwd(){

    char cwd[300];

    if(getcwd(cwd, sizeof(cwd)) == NULL){
        perror("getcwd() error");
    }else{
        printf("Diretório Atual: %s\n", cwd);
    }
}


int leitura_string(char *entrada_usuario){
    if(strcmp(entrada_usuario, "ls") == 0){
        ls();
        return 1;
    }
    else if(strcmp(entrada_usuario, "cd") == 0){
        cd();
        return 1;
    }
    else if(strcmp(entrada_usuario, "pwd") == 0){
        pwd();
        return 1;
    }
    return 0;
    
}