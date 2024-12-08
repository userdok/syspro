#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
    char str[1024];
    char *command1, *args1[10];
    char *command2, *args2[10];
    int fd[2];

    printf("[shell]");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    if (strchr(str, '|') != NULL) {
        command1 = strtok(str, "| ");
        command2 = strtok(NULL, "| ");
    } else {
        fprintf(stderr, "Error: Invalid command. Use 'command1 | command2'.\n");
        exit(1);
    }

    int i = 0;
    char *token = strtok(command1, " ");
    while (token != NULL) {
        args1[i++] = token;
        token = strtok(NULL, " ");
    }
    args1[i] = NULL;

    i = 0;
    token = strtok(command2, " ");
    while (token != NULL) {
        args2[i++] = token;
        token = strtok(NULL, " ");
    }
    args2[i] = NULL;

    pipe(fd);

    if (fork() == 0) {
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
        execvp(args1[0], args1);
        perror("execvp command1");
        exit(1);
    }

    if (fork() == 0) {
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        execvp(args2[0], args2);
        perror("execvp command2");
        exit(1);
    }

    close(fd[READ]);
    close(fd[WRITE]);
    wait(NULL);
    wait(NULL);

    return 0;
}
