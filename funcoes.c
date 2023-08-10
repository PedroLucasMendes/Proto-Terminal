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


void leitura_string(char *entrada_usuario){
    if(strcmp(entrada_usuario, "ls") == 0){
        ls();
    }
    else if(strcmp(entrada_usuario, "cd") == 0){
        cd();
    }
    else if(strcmp(entrada_usuario, "pwd") == 0){
        pwd();
    }
    
}