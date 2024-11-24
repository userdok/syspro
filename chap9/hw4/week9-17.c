#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 100
#define MAXCMD 1024

int main() {
    char command[MAXCMD];
    char *args[MAXARG];
    char *saveptr;
    int background;

    while (1) {
        printf("Pls input cmd : ");
        if (fgets(command, MAXCMD, stdin) == NULL) {
            perror("Error read input\n");
            continue;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            printf("[%d] Parent process start\n", getpid());
            printf("Parent process end\n");
            printf("Exit\n");
            break;
        }

        background = 0;
        if (command[strlen(command) - 1] == '&') {
            background = 1;
            command[strlen(command) - 1] = '\0';
        }

        char *token = strtok_r(command, " ", &saveptr);
        int i = 0;
        while (token != NULL && i < MAXARG - 1) {
            args[i++] = token;
            token = strtok_r(NULL, " ", &saveptr);
        }
        args[i] = NULL;

        if (args[0] == NULL) { 
            continue;
        }

        printf("[%d] Parent process start\n", getpid());

        int pid = fork();
        if (pid < 0) {
            perror("Fork fail\n");
            continue;
        }

        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Command execution failed");
                exit(EXIT_FAILURE);
            }
        } else {
            if (!background) {
                int status;
                waitpid(pid, &status, 0);
                printf("SUCCESS\n");
            } else {
                int status;
                waitpid(pid, &status, WNOHANG);
                printf("SUCCESS\n");
            }
        }
    }
    return 0;
}
