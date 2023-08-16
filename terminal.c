#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "funcoes.h"
#include "parser.h"

int main(){
    char entrada_usuario[100];
    char *executavel = malloc(sizeof(char)*100);
    printf(">>> ");
    while(scanf("%[^\n]%*c", entrada_usuario), strcmp(entrada_usuario, "exit") != 0){
        entrada_t *program_args = quebra_entrada(entrada_usuario);
        int cont = leitura_string(GetPrograma(program_args));
        if(cont == 1){
            ls();
        }else if(cont == 2){
            char** vetor = GetArgs(program_args);
            cd(vetor[0]);
        }else if(cont == 3){
            pwd();
        }else if(VerificaExecutavel(GetPrograma(program_args),executavel)){
            
            int rc = fork();
            if (rc < 0) {// fork falhou
                fprintf(stderr, "fork falhou\n");
                exit(1);
            } else if (rc == 0) { // filho
                char *myargs[GetQuantItens(program_args)+1];
                int i = 1;
                char **args = GetArgs(program_args);
                myargs[0] = strdup(executavel);   // programa: "wc"
                for(i; i <= GetQuantItens(program_args); i++){
                    myargs[i] = strdup(args[i-1]);
                }
                myargs[i] = NULL;
                execvp(myargs[0], myargs);  // roda wc
                printf("Isso nao deve ser imprimido");
            } else {// Pai vem por aqui
                int wc = wait(NULL);
            }
        }
        
        printf(">>> ");
    }
}