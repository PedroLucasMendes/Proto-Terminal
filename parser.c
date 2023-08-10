// Este arquivo está destinado a conter o parser do terminal, eu ja to desesperado aqui
#include "stdio.h"
#include <string.h>
#include "stdlib.h"

typedef struct entrada{
    char *programa;
    char **args;
    int quantidade_elementos;
}entrada;

char **quebra_entrada(char entrada[]) {
    char **saida = malloc(sizeof(char *) * 6); // Aumentado para 6 para lidar com o caso de 5 palavras
    int iterador = 0; // Inicialização corrigida para 0
    char *token;

    for (int i = 0; i < 6; i++) {
        saida[i] = malloc(sizeof(char) * 50); // Aumentado para 50 caracteres por string
        if (saida[i] == NULL) {
            printf("Erro ao alocar memoria");
            exit(EXIT_FAILURE);
        }
    }

    token = strtok(entrada, " ");
    while (token != NULL) {
        strcpy(saida[iterador], token);
        token = strtok(NULL, " ");
        iterador++;
    }

    saida[iterador] = NULL; // Marcando o final do vetor de strings

    return saida;
}

void printa_saida(char **saida) {
    int iterador = 0;
    while (saida[iterador] != NULL) {
        printf("%s\n", saida[iterador]);
        iterador++;
    }
}


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


int main() {
    char entradas[50] = "Luan Carlos Alencar";
    char **aaa = quebra_entrada(entradas);
    printa_saida(aaa);

    // Liberar a memória alocada
    for (int i = 0; i < 6; i++) {
        free(aaa[i]);
    }
    free(aaa);

    return 0;
}

