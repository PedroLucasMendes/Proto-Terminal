#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    printf("mostrando caminho do diretorio atual:\n");
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