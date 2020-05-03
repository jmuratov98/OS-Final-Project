#include<stdio.h>       // C Rename function is included in this header
#include<stdlib.h>      // C Standard Library 
#include<unistd.h>      // Unix Standard Library 


int main() 
{    
    char s[100];                            // Memory buffer 
    printf("Current Working Directory:\n\t%s\n", getcwd(s, 100));         // This prints the current working directory     
    // So this is essentially how the $ pwd command works in linux ... 
    
    FILE * fp;

    char old_name[] = "t2.txt";              // original file name 
    char new_name[] = "path-info.txt";       // new file name 

    fp = fopen(old_name, "w+");
    fprintf(fp, "This is testing for fprintf ... \n");
    fprintf(fp, "Current Working Directory:\n\t%s\n", getcwd(s, 100));    // This prints the current working directory into the "t2.txt" file 
    fclose(fp);                 // Close file 

    printf("\nCurrent Working Directory path added to file t2.txt\n");

    int value = rename(old_name, new_name);         // rename "t2.txt" to "path-info.txt" [FILE MUST BE CLOSED!] 

    // Standard Exception Handling 
    if(!value) { 
        printf("%s", "-- File name changed successfully!\n"); 
    } else { 
        perror("\nError File name change unsuccess!\n"); 
    } 

/* ---------------------------------[  Thought Process:  ]-------------------------------------
Open 2 files in read mode, store all of its content and paste into a 3rd file 't3.txt', 
after closing the file, rename 't3.txt' into 'log.txt' and then delete the first 2 files.
----------------------------------------------------------------------------------------------- */

    FILE *fs1, *fs2, *logFile;

    char ch, file1[100], file2[100], file3[200];

    fs1 = fopen("tree.txt", "r");     // Open file 1 in read mode 
    fs2 = fopen("path.txt", "r");     // Open file 2 in read mode 

    // Standard Exception Handling for tree.txt, and path.txt
    if( fs1 == NULL || fs2 == NULL ) {
		perror("Error ");
		printf("Press any key to exit...\n");
		exit(EXIT_FAILURE);
	}

    logFile = fopen("t3.txt", "w");    // Open log file write mode
    
    // Standard Exception Handling for t3.txt
    if( logFile == NULL ) {
		perror("Error ");
		printf("Press any key to exit...\n");
		exit(EXIT_FAILURE);
	}

    while( ( ch = fgetc(fs1) ) != EOF )
	      fputc(ch,logFile);
	while( ( ch = fgetc(fs2) ) != EOF )
	      fputc(ch,logFile);

    char filename[] = "t3.txt";              // original file name 
    char new_filename[] = "log.txt";         // new file name 

    printf("Two files were sucessfully merged into %s file successfully!\n", filename);

    fclose(fs1);            // close file 1 
	fclose(fs2);            // close file 2 
    fclose(logFile);        // close logFile 

    int result = rename(filename, new_filename);        // rename "t3.txt" to "log.txt" [FILE MUST BE CLOSED!] 

    // Standard Exception Handling 
    if(!result) { 
        printf("%s", " -- File name changed successfully!\n"); 
    } else { 
        perror("\nError File name change unsuccess!\n"); 
    } 

    printf("\n");       // Just for formatting purposes


    // Now all that's left is to delete the remaining 2 files! 

    remove("tree.txt");     // delete "tree.txt"
    printf("tree.txt file removed successfully ...\n");
    remove("path.txt");     // delete "path.txt"
    printf("path.txt file removed successfully ...\n");

    printf("\nAll tasks done!\n\nProgram Execution Complete!\n");

    return 0; 

} 
