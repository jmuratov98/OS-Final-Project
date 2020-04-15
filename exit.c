int main(int argc, char* argv[]){
    for(int i=0;i<4;i++){
        char* argument = argv[i + 1];
        printf("History Command is %s\n", argument);
    }
    printf("Enter 'Return key' back to main menu \n");
    while(1)
    {       
        char input = getchar();
        if(input == '\n')         
            break;      
    }
}