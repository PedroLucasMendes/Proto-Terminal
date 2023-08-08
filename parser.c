// Este arquivo está destinado a conter o parser do terminal, eu ja to desesperado aqui
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct entrada{
    char *programa;
    char **args;
    int quantidade_elementos;
}entrada;

entrada *tratamento_entrada(char entrada_completa[]){
    int contador = 0;
    char delimitador[2] = " ";
    char *prog = malloc(sizeof(char)*20); //executavel
    
    printf("oie");
    entrada *entrada_usuario = malloc(sizeof(entrada)); //alocar pra estrutura
    entrada_usuario->args = malloc(sizeof(char*)*10);
    for(int i = 0; i < 10; i++){
        entrada_usuario->args[i] = malloc(sizeof(char)*10);
    }
    entrada_usuario->programa = strtok(entrada_completa, delimitador); // pegar programa da string total

    while(entrada_completa != NULL){
        entrada_usuario->args[contador] = strtok(NULL, delimitador);
        contador++;
    }

    entrada_usuario->quantidade_elementos = contador+1;
    printf("%s", entrada_usuario->programa);
    for(int i = 0; i < contador; i++){
        printf("%s", entrada_usuario->args[i]);
    }
    printf("%d", entrada_usuario->quantidade_elementos);
    return entrada_usuario;

}

int main(){
    char entrada[50];
    scanf("%[^\n]%*c",entrada);
    entrada *teste = tratamento_entrada(entrada);


}
