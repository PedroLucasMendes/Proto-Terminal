#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

/*
este arquivo contem as funcoes que serao chamadas no arquivo terminal.c
*/
void ls(char** args, int num_args){
    char** new_args = (char**)malloc((num_args + 2) * sizeof(char*));
    if (new_args == NULL) {
        perror("malloc");
        exit(1);
    }

    new_args[0] = "ls";
    for (int i = 1; i < num_args+1; i++) {
        new_args[i] = strdup(args[i-1]);
        if (new_args[i] == NULL) {
            perror("strdup");
            exit(1);
        }
    }
    new_args[num_args+2] = 0;
    int rc = fork();
    if (rc < 0) {// fork falhou
        fprintf(stderr, "fork falhou\n");
        exit(1);
    } 
    else if (rc == 0) { // filho
        execvp("ls",new_args);  // roda wc
        printf("Isso nao deve ser imprimido");
    } 
    else {
        int wc = wait(NULL);
    }
}

void cd(char* caminho){
    if(chdir(caminho) == 0){
        //printf("Caminho alterado para %s\n",caminho);
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
    int cont = 1;
    for(int i = 0; i < quantArgs; i++){
        if(strcmp(args[i],"|") == 0){
            return cont;
        }
        cont++;
    }
    return 0;
}



