#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipe_fds[2]; // Descritores de arquivo para o pipe

    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        return 1;
    }

    int sum_pid, mul_pid;

    sum_pid = fork();
    if (sum_pid == 0) {
        // Filho 1 - Soma
        close(pipe_fds[0]); // Fecha a extremidade de leitura do pipe no filho
        dup2(pipe_fds[1], STDOUT_FILENO); // Redireciona a saída padrão para o pipe
        close(pipe_fds[1]); // Fecha a extremidade de escrita do pipe no filho
        char *myargs[2];
        myargs[0] = strdup("./hello");   // programa: "wc"
        myargs[1] = NULL;
        execvp(myargs[0], myargs);  // roda wc
        perror("Erro ao executar o programa de soma");
        exit(1);
    } else if (sum_pid > 0) {
        // Pai
        mul_pid = fork();
        if (mul_pid == 0) {
            // Filho 2 - Multiplicação
            close(pipe_fds[1]); // Fecha a extremidade de escrita do pipe no filho
            dup2(pipe_fds[0], STDIN_FILENO); // Redireciona a entrada padrão para o pipe
            close(pipe_fds[0]); // Fecha a extremidade de leitura do pipe no filho
            char *myargs[2];
            myargs[0] = strdup("./hello2");   // programa: "wc"
            myargs[1] = NULL;
            execvp(myargs[0], myargs);  // roda wc
            perror("Erro ao executar o programa de multiplicação");
            exit(1);
        } else if (mul_pid > 0) {
            // Pai
            close(pipe_fds[0]); // Fecha as extremidades do pipe no pai
            close(pipe_fds[1]);

            // Espera pelos filhos
            waitpid(sum_pid, NULL, 0);
            waitpid(mul_pid, NULL, 0);
        } else {
            perror("fork mul_program");
            return 1;
        }
    } else {
        perror("fork sum_program");
        return 1;
    }

    return 0;
}
