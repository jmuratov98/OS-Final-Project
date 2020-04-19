#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// GOAL: implement the following command :  clear & ls -l | tee text.txt & mv text.txt test.txt
int main(int argc, char** argv)
{
    pid_t pclear_id, pls_id, ptee_id, pmv_id; // create all process id
    int mypipe[2];
    chdir("./Dir0/");
    pipe(mypipe);
    printf("child%d\n",1);
    if((pclear_id = fork()) < 0) {
        // error forking child
        perror("Error forking child");
        return 1;
    } else if(pclear_id == 0) {
        printf("child1");
        execlp("clear", "clear", NULL); 
    } 

    wait(NULL);
    printf("child%d\n",2);
    // Parent process
    if((pls_id = fork()) < 0) { // Error checking
        perror("Error forking child");
        return 1;
    } else if(pls_id == 0) {
        
        dup2(mypipe[1], 1);
        execlp("ls", "ls", "-l", NULL); 
    } 

    wait(NULL);
    printf("child%d\n",3);
    if((ptee_id = fork()) < 0) {
        perror("Error forking child");
        return 1;
    } else if(ptee_id == 0){
    
        execlp("sh", "sh", "-c", "ls -l > t1.txt", (char *)0);
    }

            
    wait(NULL); 
    printf("child%d\n",4);
    if((pmv_id = fork()) < 0) {
        perror("Error forking child");
        return 1;
    } else if(pmv_id == 0) {
        printf("child4");
        execlp("cp", "cp", "t1.txt", "tree.txt", NULL);
    }

    wait(NULL);         
    
    return 0;
}