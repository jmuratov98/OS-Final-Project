#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(int argc, char* argv[]){
    int size = 0;
    for(int i=0;i<4;i++){
        if(!argv[i])
            break;
        size++;
    }

    for(int i=size;i > 0;i--){
        printf("History Command is %s\n", argv[i-1]);
    }

    pid_t pid;
    pid = fork(); // Create child 1

    if (pid < 0) // Error forking
    {
        perror("Failed to fork a child");
        exit(1);
    }
    else if (pid == 0) // Child process
    {
        printf("\nPrint current directory\n");
       execlp("ls", "ls", "-l", NULL);
    }
    else{
        wait(NULL);
        printf("\nEnter 'Return key' back to main menu \n");
        while(1)
        {       
            char input = getchar();
            if(input == '\n')         
                break;      
        }
    }

}
