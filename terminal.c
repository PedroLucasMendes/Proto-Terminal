#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "funcoes.h"
#include "parser.h"

int main(){
    char entrada_usuario[100];
    printf(">>> ");
    while(scanf("%[^\n]%*c", entrada_usuario), strcmp(entrada_usuario, "exit") != 0){
        entrada_t *program_args = quebra_entrada(entrada_usuario);
        int cont = leitura_string(GetPrograma(program_args));
        if(cont == 1){
            ls(GetArgs(program_args));
        }else if(cont == 2){
            char** vetor = GetArgs(program_args);
            cd(vetor[0]);
        }else if(cont == 3){
            pwd();
        }else if(VerificaExecutavel(GetPrograma(program_args)) && GetQuantItens(program_args) > 0 && !VerificaPipe(GetArgs(program_args),GetQuantItens(program_args))){
            printf("oie");
            if(strcmp(GetArgs(program_args)[0],"&") == 0){
                int rc = fork();
                if (rc < 0) {// fork falhou
                    fprintf(stderr, "fork falhou\n");
                    exit(1);
                } else if (rc == 0) { // filho
                    char *myargs[GetQuantItens(program_args)];
                    int i = 1;
                    char **args = GetArgs(program_args);
                    VerificaIO(GetArgs(program_args),GetQuantItens(program_args));
                    myargs[0] = strdup(GetPrograma(program_args));   // programa: "wc"
                    for(i; i <= GetQuantItens(program_args); i++){
                        myargs[i] = strdup(args[i-1]);
                    }
                    myargs[i] = NULL;
                    execvp(myargs[0], myargs);  // roda wc
                    printf("Isso nao deve ser imprimido");
                } else {// Pai vem por aqui
                }
            }else{
                int rc = fork();
                if (rc < 0) {// fork falhou
                    fprintf(stderr, "fork falhou\n");
                    exit(1);
                } else if (rc == 0) { // filho
                    char *myargs[GetQuantItens(program_args)];
                    int i = 1;
                    char **args = GetArgs(program_args);
                    VerificaIO(GetArgs(program_args),GetQuantItens(program_args));
                    myargs[0] = strdup(GetPrograma(program_args));   // programa: "wc"
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
        }else if(VerificaExecutavel(GetPrograma(program_args)) && GetQuantItens(program_args) == 0 && !VerificaPipe(GetArgs(program_args),GetQuantItens(program_args))){
            int rc = fork();
            if (rc < 0) {// fork falhou
                fprintf(stderr, "fork falhou\n");
                exit(1);
            } else if (rc == 0) { // filho
                char *myargs[2];
                char **args = GetArgs(program_args);
                VerificaIO(GetArgs(program_args),GetQuantItens(program_args));
                myargs[0] = strdup(GetPrograma(program_args));   // programa: "wc"
                myargs[1] = NULL;
                execvp(myargs[0], myargs);  // roda wc
                printf("Isso nao deve ser imprimido");
            } else {// Pai vem por aqui
                int wc = wait(NULL);
            }
        }else if(VerificaExecutavel(GetPrograma(program_args)) && GetQuantItens(program_args) > 0 && !VerificaIO(GetArgs(program_args),GetQuantItens(program_args)) && VerificaPipe(GetArgs(program_args),GetQuantItens(program_args))){
            int pipe_fds[2]; // Descritores de arquivo para o pipe
            int posicao_pipe = VerificaPipe(GetArgs(program_args),GetQuantItens(program_args));
            
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                return 1;
            }

            int process_pid1, process_pid2;
            
            process_pid1 = fork();
            if (process_pid1 == 0) {
                // Filho 1 - Soma
                close(pipe_fds[0]); // Fecha a extremidade de leitura do pipe no filho
                dup2(pipe_fds[1], STDOUT_FILENO); // Redireciona a saída padrão para o pipe
                close(pipe_fds[1]); // Fecha a extremidade de escrita do pipe no filho
                char *myargs[2];
                myargs[0] = strdup(GetPrograma(program_args));   // programa: "wc"
                myargs[1] = NULL;
                execvp(myargs[0], myargs);  // roda wc
                perror("Erro ao executar o programa de soma");
                exit(1);
            } else if (process_pid1 > 0) {
                // Pai
                char program[100] = "./";
                process_pid2 = fork();
                if (process_pid2 == 0) {
                    // Filho 2 - Multiplicação
                    close(pipe_fds[1]); // Fecha a extremidade de escrita do pipe no filho
                    dup2(pipe_fds[0], STDIN_FILENO); // Redireciona a entrada padrão para o pipe
                    close(pipe_fds[0]); // Fecha a extremidade de leitura do pipe no filho
                    char *myargs[2];
                    strcat(program,GetArgs(program_args)[posicao_pipe]);
                    myargs[0] = strdup(program);   // programa: "wc"
                    myargs[1] = NULL;
                    execvp(myargs[0], myargs);  // roda wc
                    perror("Erro ao executar o programa de multiplicação");
                    exit(1);
                } else if (process_pid2 > 0) {
                    // Pai
                    close(pipe_fds[0]); // Fecha as extremidades do pipe no pai
                    close(pipe_fds[1]);

                    // Espera pelos filhos
                    waitpid(process_pid1, NULL, 0);
                    waitpid(process_pid2, NULL, 0);
                } else {
                    perror("fork mul_program");
                    return 1;
                }
            } else {
                perror("fork sum_program");
                return 1;
            }
        }else{
            int rc = fork();
            if (rc < 0) {// fork falhou
                fprintf(stderr, "fork falhou\n");
                exit(1);
            } else if (rc == 0) { // filho
                char *myargs[GetQuantItens(program_args)];
                int i = 1;
                char **args = GetArgs(program_args);
                myargs[0] = strdup(GetPrograma(program_args));   // programa: "wc"
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