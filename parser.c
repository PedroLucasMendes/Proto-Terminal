// Este arquivo está destinado a conter o parser do terminal, eu ja to desesperado aqui
#include "stdio.h"
#include <string.h>
#include "stdlib.h"

typedef struct entrada{
    char *programa;
    char **args;
    int quantidade_elementos;
}entrada;


int conta_argumentos(char **lista_de_args){
    int contador = 0;
    while(lista_de_args[contador] != NULL){
        contador ++;
    }
    contador--;
    return contador;
}

char *GetPrograma(entrada *strc_program){
    return strc_program->programa;
}

char **GetArgs(entrada *strc_args){
    return strc_args->args;
}

int GetQuantItens(entrada *strc_quant){
    return strc_quant->quantidade_elementos;
}

entrada *aloca_entrada(char **lista_de_args){
    entrada *argumentos = malloc(sizeof(entrada));
    argumentos->programa = malloc(sizeof(char)*10);
    strcpy(argumentos->programa, lista_de_args[0]);
    printf("%s\n",argumentos->programa);
    argumentos->quantidade_elementos = conta_argumentos(lista_de_args);
    printf("%d\n",argumentos->quantidade_elementos);
    argumentos->args = malloc(sizeof(char*) * argumentos->quantidade_elementos);

    for(int iterador = 0; iterador < argumentos->quantidade_elementos; iterador++ ){
        argumentos->args[iterador] = malloc(sizeof(char)*10);
        strcpy(argumentos->args[iterador], lista_de_args[iterador+1]);
        printf("%s\n",argumentos->args[iterador]);
        if(argumentos->args[iterador] == NULL){
            printf("Erro ao alocar memoria\n");
        }
    }
    return argumentos;
}


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


void printa_struct(entrada* Entrada){
    printf("executavel: %s\n", Entrada->programa);
    for(int iterador = 0; iterador < Entrada->quantidade_elementos; iterador++){
        printf("argumento %d: %s\n", iterador, Entrada->args[iterador]);
    }
    printf("quantidade de argumentos: %d\n", Entrada->quantidade_elementos);
}


int main() {
    char entradas[50] = "Luan Carlos Alencar";
    char **aaa = quebra_entrada(entradas);
    entrada *teste = aloca_entrada(aaa);
    printa_saida(aaa);
    printf("%d", conta_argumentos(aaa));
    printa_struct(teste);
    




    // Liberar a memória alocada
    for (int i = 0; i < 6; i++) {
        free(aaa[i]);
    }
    free(aaa);

    return 0;
}

