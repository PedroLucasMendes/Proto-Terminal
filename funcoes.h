#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcoes.c"

int leitura_string(char *entrada_usuario);
void ls(char** args, int num_args);
void cd(char* caminho);
void pwd();
int VerificaExecutavel(char *string);
int VerificaIO(char **args, int quantArgs);
int VerificaPipe(char **args, int quantArgs);