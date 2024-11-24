#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_CMD 1024
#define MAX_ARGS 100

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    char *redir_in = NULL, *redir_out = NULL;
    int background = 0;
    int i = 0;
    char *token = strtok(cmd, " ");

    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            background = 1;
        } else if (strcmp(token, ">") == 0) {
            redir_out = strtok(NULL, " ");
        } else if (strcmp(token, "<") == 0) {
            redir_in = strtok(NULL, " ");
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    pid_t pid = fork();

    if (pid == 0) {
        if (redir_in) {
            int fd = open(redir_in, O_RDONLY);
            if (fd < 0) {
                perror("Input fail\n");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (redir_out) {
            int fd = open(redir_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Output fail\n");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }


        execvp(args[0], args);
        perror("Run fail\n");
        exit(1);
    } else if (pid > 0) {
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("Background PID: %d\n", pid);
        }
    } else {
        perror("Process creation fail\n");
    }
}

int main() {
    char input[MAX_CMD];

    while (1) {
        printf("[shell] ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) break;
        char *cmd = strtok(input, ";");
        while (cmd != NULL) {
            execute_command(cmd);
            cmd = strtok(NULL, ";");
        }
    }
    return 0;
}
