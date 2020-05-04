#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// GOAL: implement the following command :  clear & ls -l | tee text.txt & mv text.txt test.txt
int main(int argc, char **argv)
{
    pid_t pclear_id, pls_id, pmv_id, pcat_id; // create all process id
    int mypipe[2];

    int status;

    pipe(mypipe);

    chdir("./Dir0"); // Changes Directory

    pclear_id = fork();
    if (pclear_id < 0)
    {
        perror("[ERROR] Forking clear child");
        return 1;
    }
    else if (pclear_id == 0)
    {
        // no need for pipe
        close(mypipe[0]);
        close(mypipe[1]);

        execlp("clear", "clear", NULL);
    }
    else
        wait(&status);

    if (WIFEXITED(status))
    {
        pls_id = fork();
        if (pls_id < 0)
        {
            perror("[ERROR] Forking child");
            return 1;
        }
        else if (pls_id == 0)
        {
            close(mypipe[0]);

            // dup2(mypipe[1], 1);
            execlp("sh", "sh", "-c", "ls -l > t1.txt", (char*)0);

            close(mypipe[1]);
        }
        else
            wait(&status);
    }

    if (WIFEXITED(status))
    {
        pmv_id = fork();
        if (pmv_id < 0)
        {
            perror("[ERROR] Forking child");
            return 1;
        }
        else if (pmv_id == 0)
        {
            close(mypipe[0]);
            close(mypipe[1]);

            dup2(mypipe[0], 0);
            execlp("mv", "mv", "t1.txt", "tree.txt", NULL);
        }
        else
            wait(&status);
    }

    if (WIFEXITED(status))
    {
        pcat_id = fork();
        if (pcat_id < 0)
        {
            perror("[ERROR] Forking child");
            return 1;
        }
        else if (pcat_id == 0)
        {
            execlp("cat", "cat", "tree.txt", NULL);
        }
        else {
            close(mypipe[0]);
            close(mypipe[1]);
            wait(&status);
        }
    }

    return 0;
}
