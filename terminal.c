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
            ls(GetArgs(program_args), GetQuantItens(program_args));
        }else if(cont == 2){
            char** vetor = GetArgs(program_args);
            cd(vetor[0]);
        }else if(cont == 3){
            pwd();
        }else if(VerificaExecutavel(GetPrograma(program_args)) && GetQuantItens(program_args) > 0 && !VerificaPipe(GetArgs(program_args),GetQuantItens(program_args))){
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
            } else {// Pai vem por aqui
                int wc = wait(NULL);
            }
        }else if(GetQuantItens(program_args) <= 2 && !VerificaIO(GetArgs(program_args),GetQuantItens(program_args)) && VerificaPipe(GetArgs(program_args),GetQuantItens(program_args))){
            int pipe_fds[2]; 
            int posicao_pipe = VerificaPipe(GetArgs(program_args),GetQuantItens(program_args));
            printf("para 1\n");
            if (pipe(pipe_fds) == -1) {
                perror("Erro no pipe");
                return 1;
            }

            int process_pid1, process_pid2;
            
            process_pid1 = fork();
            if (process_pid1 == 0) {
                close(pipe_fds[0]); 
                dup2(pipe_fds[1], STDOUT_FILENO); 
                close(pipe_fds[1]); 
                char *myargs[2];
                myargs[0] = strdup(GetPrograma(program_args));   // programa: "wc"
                myargs[1] = NULL;
                execvp(myargs[0], myargs);  // roda wc
                perror("Erro ao executar o programa");
                exit(1);
            } else if (process_pid1 > 0) {
                // Pai
                char program[100] = "./";
                process_pid2 = fork();
                if (process_pid2 == 0) {
                    
                    close(pipe_fds[1]); 
                    dup2(pipe_fds[0], STDIN_FILENO); 
                    close(pipe_fds[0]); 
                    char *myargs[2];
                    strcat(program,GetArgs(program_args)[posicao_pipe]);
                    myargs[0] = strdup(program);   // programa: "wc"
                    myargs[1] = NULL;
                    execvp(myargs[0], myargs);  // roda wc
                    perror("Erro ao executar o programa");
                    exit(1);
                } else if (process_pid2 > 0) {
                    // Pai
                    close(pipe_fds[0]); 
                    close(pipe_fds[1]);

                    // Espera pelos filhos
                    waitpid(process_pid1, NULL, 0);
                    waitpid(process_pid2, NULL, 0);
                } else {
                    perror("Erro fork");
                    return 1;
                }
            } else {
                perror("Erro fork");
                return 1;
            }
        }else if(GetQuantItens(program_args) > 2 && !VerificaIO(GetArgs(program_args),GetQuantItens(program_args)) && VerificaPipe(GetArgs(program_args),GetQuantItens(program_args))){
            int pipe_fds[2]; 
            int posicao_pipe = VerificaPipe(GetArgs(program_args),GetQuantItens(program_args));
            
            if (pipe(pipe_fds) == -1) {
                perror("Erro pipe");
                return 1;
            }

            int process_pid1, process_pid2;
            
            process_pid1 = fork();
            if (process_pid1 == 0) {
                
                
                close(pipe_fds[0]); 
                dup2(pipe_fds[1], STDOUT_FILENO); 
                
                close(pipe_fds[1]);
                
                char *myargs[posicao_pipe+1];
                char **args = GetArgs(program_args);
                int i = 1;
                VerificaExecutavel(GetPrograma(program_args));
                myargs[0] = strdup(GetPrograma(program_args));
                
                for(i = 1; i < VerificaPipe(GetArgs(program_args),GetQuantItens(program_args)); i++){


                    myargs[i] = strdup(args[i-1]);
                }
               
                myargs[i] = NULL;
                
                execvp(myargs[0], myargs);  // roda wc
                perror("Erro ao executar o programa");
                exit(1);
            } else if (process_pid1 > 0) {
                int wc = wait(NULL);
                // Pai
                process_pid2 = fork();
                if (process_pid2 == 0) {
                    close(pipe_fds[1]); 
                    dup2(pipe_fds[0], STDIN_FILENO); 
                    close(pipe_fds[0]);
                    char *myargs[(GetQuantItens(program_args)-posicao_pipe)+1];
                    char **args = GetArgs(program_args);
                    int i = VerificaPipe(GetArgs(program_args),GetQuantItens(program_args));
                    
                    VerificaExecutavel(GetArgs(program_args)[i]);
                    myargs[0] = strdup(GetArgs(program_args)[i]);   // programa: "wc"
                    int j,cont = 1;
                    for(j = i+1; j < GetQuantItens(program_args); j++){
                        myargs[cont] = strdup(args[j]);
                        cont++;
                    }
                    myargs[cont] = NULL;
                    execvp(myargs[0], myargs);  // roda wc
                    perror("Erro ao executar o programa");
                    exit(1);
                } else if (process_pid2 > 0) {
                    // Pai
                    close(pipe_fds[0]); 
                    close(pipe_fds[1]);

                    // Espera pelos filhos
                    waitpid(process_pid1, NULL, 0);
                    waitpid(process_pid2, NULL, 0);
                } else {
                    perror("error fork");
                    return 1;
                }
            } else {
                perror("error fork");
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
            } else {// Pai vem por aqui
                int wc = wait(NULL);
            }
        }
        
        printf(">>> ");
    }
}