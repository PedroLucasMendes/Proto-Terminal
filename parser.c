// Este arquivo está destinado a conter o parser do terminal, eu ja to desesperado aqui
#include "stdio.h"
#include <string.h>
#include "stdlib.h"

typedef struct entrada{
    char *programa;
    char **args;
    int quantidade_elementos;
}entrada;

entrada *criar_entrada(char entrada_completa[]){

    entrada *entrada_usuario = malloc(sizeof(entrada)); //alocar pra estrutura
    entrada_usuario->programa = malloc(sizeof(char)*10);

    //Função encontrar programa

    entrada_usuario->args = malloc(sizeof(char*)*10);
    for(int i = 0; i < 10; i++){
        entrada_usuario->args[i] = malloc(sizeof(char)*10);
        //Função adicionar argumentos

    }
    //Função que ver a quantidade de argumentos
    entrada_usuario->quantidade_elementos = 0;
    return entrada_usuario;

}

int main(){
    char entradas[50];
    //scanf("%[^\n]%*c",entradas);
    entrada *teste = tratamento_entrada("ls -l mn");


}
