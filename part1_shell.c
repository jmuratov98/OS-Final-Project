// TODO: Include error checks

#include <stdio.h>
#include <sys/wait.h> // For wait()
#include <unistd.h> // For fork() and getpid()
#include <stdlib.h>
#include <string.h>

void shell_loop();
char* read_line(void);
int execute(char *arg);

int main(int argc, char *argv[]) {
    shell_loop();
    return 0;
}

void shell_loop() {
    char* arg;
    int exit;

    do {
        printf("~ ");
        arg = read_line();
        exit = execute(arg);
    } while(!exit);

    free(arg);
}

char* read_line(void) {
    char* buf = NULL;
    size_t bufsize = 5;
    getline(&buf, &bufsize, stdin);
    return buf;
}

int execute(char *arg) {
    pid_t pid;
    int exit;

    pid = fork();

    if(pid < 0) {
        perror("fork");
    }
    else if (pid == 0) {
        // Child process
        if(strncmp(arg, "tree*", 5) == 0) {
            execl("tree*", NULL);
        }
        else if(strncmp(arg, "list*", 5) == 0) {
            execl("part3", NULL);
        }
        else if(strncmp(arg, "path*", 5) == 0) {
            execl("path*", NULL);
        }
        else if(strncmp(arg, "exit*", 5) == 0) {
            execl("exit_process", NULL);
        }
    }

    // Parent process
    wait(NULL);

    if(strncmp(arg, "exit*", 5) == 0) {
        return 1;
    }

    return 0;
}
