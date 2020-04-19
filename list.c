#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// GOAL: implement the following command :  clear & ls -l | tee text.txt & mv text.txt test.txt
int main(int argc, char** argv)
{
    pid_t pclear_id, pls_id, ptee_id, pmv_id; // create all process id
    int mypipe[2];

    // Create pipe
    pipe(mypipe);

    chdir("./Dir0/");

    if((pclear_id = fork()) < 0) {
        // error forking child
        perror("Error forking child");
        return 1;
    } else if(pclear_id == 0) {
        // Child process

        // No need for pipe here
        if(close(mypipe[0]) == -1) {
            perror("Error closing pipe");
            return 1;
        }

        if(close(mypipe[1]) == -1) {
            perror("Error closing pipe");
            return 1;
        }

        // Executes the clear command
        execlp("clear", "clear", NULL);
    } else {
        // Parent process
        if((pls_id = fork()) < 0) { // Error checking
            perror("Error forking child");
            return 1;
        } else if(pls_id == 0) {
            // No need to read from processes
            if(close(mypipe[0]) == -1) {
                perror("Error closing pipe");
                return 1;
            }

            dup2(mypipe[1], 1);
            execlp("ls", "ls", "-l", NULL);

            if(close(mypipe[1]) == -1) {
                perror("Error closing pipe");
                return 1;
            }
        } else {
            if((ptee_id = fork()) < 0) {
                perror("Error forking child");
                return 1;
            } else if(ptee_id == 0) {
                if(close(mypipe[1]) == -1) {
                    perror("Error closing pipe");
                    return 1;
                }

                dup2(mypipe[0], 0);
                execlp("tee", "tee", "t1.txt", NULL);

                if(close(mypipe[0]) == -1) {
                    perror("Error closing pipe");
                    return 1;
                }
            } else {
                if((pmv_id = fork()) < 0) {
                    perror("Error forking child");
                    return 1;
                } else if(pmv_id == 0) {
                    
                    close(mypipe[0]);
                    close(mypipe[1]);

                    execlp("mv", "mv", "t1.txt", "tree.txt", NULL);

                } else {
                    close(mypipe[0]);
                    close(mypipe[1]);

                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                }
            }
        }
    }

    return 0;
}