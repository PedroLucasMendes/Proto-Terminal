#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int isProgram(char program[]){
    if(program[0] == '.' && program[1] == '/' ){
        return 1;
    }else{
        return 0;
    }
}


int main(){

    char program[50];

    scanf("%[^\n]",program);
    if(isProgram(program)){
        int rc = fork();
        if (rc < 0) {// fork falhou
            fprintf(stderr, "fork falhou\n");
            exit(1);
        } else if (rc == 0) { // filho
            char *myargs[3];
            myargs[0] = strdup(program);   // programa: "wc"
            myargs[0] = strdup(program);
            myargs[1] = NULL; // argumento: nome do arquivo
            execvp(myargs[0], myargs);  // roda wc
            printf("Arquivo não está no diretorio\n");
        } else {// Pai vem por aqui
            int wc = wait(NULL);
        }
        return 0;
    }else{
        printf("Não e");
    }

    return 0;
}