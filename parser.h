typedef struct entrada entrada_t;

int conta_argumentos(char **lista_de_args);

char *GetPrograma(entrada_t *strc_program);

char **GetArgs(entrada_t *strc_args);

int GetQuantItens(entrada_t *strc_quant);

entrada_t* quebra_entrada(char entrada[]);

void printa_struct(entrada_t* Entrada);