#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h> 


int wordcount(const char *text, int newLine) {
    int count = 0;
    int inbtw = 0;

    for (int i = 0; text[i] != '\0'; i++) {

        if (text[i] == ' ') {

            count++;
            inbtw = 0;


        }else if(text[i] == '\t') {

            count++;
            inbtw = 0;
        }
        else if (newLine == 1 && text[i] == '\n'){

            count++;
            inbtw = 0;
        }
        else {

            inbtw = 1;

        }
    }

    if (inbtw==1) {

        count++;

    }

    return count;
}

void word(int argc, char *argv[]) {
    int newLine = 0;
    int diff = 0;
    int IndF = 1;
    int numFiles = 0;

    if (argc >= 3) {
        
        if (strcmp(argv[1], "-n") == 0){
            
            IndF++;
            numFiles = argc - IndF;
            newLine = 1;
        } 
        else if (strcmp(argv[1], "-d") == 0) {

            diff = 1;
            IndF++;
            numFiles = 2;
        }
        else{
            printf("Invalid option supplied\n");
        }
    }
    else if (argc == 2){

        numFiles = 1;

    }
    else if (argc<2){
        printf("Command line arguments invalid");
        return ;
    }

    int fileWords[numFiles];
    
    for (int i = IndF; i < argc; i++) {

        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {

            printf("File named %s doesn't exist", argv[i]);
            return ;

        }

        fseek(file, 0, SEEK_END); 
        long fileSize = ftell(file); 
        fseek(file, 0, SEEK_SET); 

        char *buffer = (char *)malloc(fileSize + 1); 
        if (buffer == NULL) {
            printf("File is empty\n");
            fclose(file);
            return;
        }

        fread(buffer, 1, fileSize, file); 
        buffer[fileSize] = '\0';
        fclose(file);

        fileWords[i - IndF] = wordcount(buffer, newLine);
    }

    if (diff && numFiles == 2){
        printf("Difference in word counts of the files %s and %s: %d\n", argv[2], argv[3], abs(fileWords[1] - fileWords[0]));
    } else {
        for (int i = 0; i < numFiles; i++) {
            printf("Word count: %d\n",fileWords[i]);
        }
    }

    return;
}

int main() {
    while (1) {
        char path[1000];
        if(getcwd(path,sizeof(path)) != NULL){
            printf("%s # ",path);
        }
        char command[100];

        char *data = fgets(command, sizeof(command), stdin);
        
        
        if (data == NULL) {
            printf("Failed to read input\n");
            return 1;
        }

        
        size_t length = strlen(command);
        if (length > 0 && command[length - 1] == '\n') {
            command[length - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            printf("\nExiting myshell.\n");
            break; 

        } 
        else {
            
            int argc = 0;
            char *argv[5]; 

            char *token = strtok(command, " ");
            while (token != NULL && argc < 3) {
                argv[argc++] = token;
                token = strtok(NULL, " ");
            }
            argv[argc] = NULL; 


            if (argc >= 2) {
                if(strcmp(argv[0],"word") == 0){
                    word(argc,argv);
                }
                else if(strcmp(argv[0],"dir") == 0){
                    int rc = fork();

                    if(rc == 0){
                        
                        // child process where we have to do execvp
                        // /mnt/c/Users/ASUS/Desktop/OSq2/dir

                        char command[100] = "/mnt/c/Users/ASUS/Desktop/OSq2/dir";
                        execvp(command,argv);
                    }
                    else{
                        // parent process
                        wait(NULL);
                        printf("changing directory to %s\n",argv[2]);
                        chdir(argv[2]);
                    }
                }
                else if(strcmp(argv[0],"date") == 0){
                    int rc = fork();

                    if(rc == 0){
                        // child process where we have to do execvp
                        // /mnt/c/Users/ASUS/Desktop/OSq2/dir
                        char command[100] = "/mnt/c/Users/ASUS/Desktop/OSq2/date";
                        execvp(command,argv);
                    }
                    else{
                        // parent process
                        wait(NULL);
                    }
                }
            
            } 
            else {
                printf("Invalid command format\n");
            }
        }
    }

    return 0; 
}