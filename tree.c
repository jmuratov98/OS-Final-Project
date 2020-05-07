#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>


int main () {   

    int file1; // Creating a new file with read and write permissions
    int file2; // Creating a second new file with read and write permissions
    int file3;// Creating a third new file with read and write permissions
    int openDir0;   // Opens dir0 and changes it into the Working Dir
    char* dirname[2] = {"Dir0", "Dir1"}; // Two Directory Names
    char* filenames[3] = {"t1.txt", "t2.txt", "t3.txt"}; // 3 Text files


    if (mkdir(dirname[0], S_IRWXU) == -1){     //Make New Directory
        perror("Error: \n");
    }
    else{
        printf("Directory %s Created\n", dirname[0]);
    }

    if((openDir0 = chdir(dirname[0])) == 0){      //Set Working Dir to Dir0
       printf("Directory %s Opened\n", dirname[0]);

       file1 = creat(filenames[0], S_IRWXU);           // Create "t1.txt"
	        if(-1 == file1){
			    printf("failed creating %s\n", filenames[0]);
			    return 1;
		    }
		    else printf("Creation of %s is successful \n", filenames[0]);
        file2 = creat(filenames[1], S_IRWXU);         // Create "t2.txt"
	        if(-1 == file2){
			    printf("failed creating %s\n", filenames[1]);
			    return 1;
		    }
		    else printf("Creation of %s is successful \n", filenames[1]);

        file3 = creat(filenames[2], S_IRWXU);        // Create "t3.txt"
	        if(-1 == file3){
			    printf("failed creating %s\n", filenames[2]);
			    return 1;
		    }
		    else printf("Creation of %s is successful \n", filenames[2]);

        if (mkdir(dirname[1], S_IRWXU) == -1){
            perror("Error: \n");
        }
        else printf("Directory %s Created\n", dirname[1]);
   }
    else printf("Failed Opening %s", dirname[0]);

    return 0;
}