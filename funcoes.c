#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

/*
este arquivo contem as funcoes que serao chamadas no arquivo terminal.c
*/
void ls(char** args){
    int rc = fork();
    if (rc < 0) {// fork falhou
        fprintf(stderr, "fork falhou\n");
        exit(1);
    } 
    else if (rc == 0) { // filho
        execvp("ls",args);  // roda wc
        printf("Isso nao deve ser imprimido");
    } 
    else {
        int wc = wait(NULL);
    }
}

void cd(char* caminho){
    if(chdir(caminho) == 0){
        printf("Caminho alterado para %s\n",caminho);
    }
    else{
        perror("erro papai");
    }
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
    if(strcmp(entrada_usuario, "ls")==0){
        return 1;
    }
    else if(strcmp(entrada_usuario, "cd") == 0){
        return 2;
    }
    else if(strcmp(entrada_usuario, "pwd") == 0){
        return 3;
    }
    return 0;
    
}

int VerificaExecutavel(char *string){
    DIR *d;
    struct dirent *dir;
    char program[100];
    char result[100] = "./";
    d = opendir(".");
    if(string[0] == '.' && string[1] == '/'){
        int i = 2;
        for(i; i < strlen(string);i++){
            program[i-2] = string[i];
        }
        program[i-2] = '\0';
    }
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name,string) == 0){
                strcat(result,string);
                strcpy(string,result);
                return 1;
            }else if(strcmp(dir->d_name,program) == 0){
                strcpy(string,string);
                return 1;
            }
        }
        closedir(d);
    }
    return 0;
    
}

int VerificaIO(char **args, int quantArgs){
    for(int i = 0; i < quantArgs; i++){
        if(strcmp(args[i],">") == 0){
            close(STDOUT_FILENO); 
            open(args[i+1], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
            return 1;
        }else if(strcmp(args[i],"<") == 0){
            close(STDIN_FILENO); 
            open(args[i+1],O_RDONLY);
        }
    }
    return 0;
}

int VerificaPipe(char **args, int quantArgs){
    int cont = 0;
    for(int i = 0; i < quantArgs; i++){
        if(strcmp(args[i],"|") == 0){
            cont++;
        }
    }
    return cont;
}

void executa_pipe(char* exec, char** args){

       int pd[2];



}



