#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///mnt/c/Users/ASUS/Desktop/OS/ques2/part1


int wordcount(const char *text, int newLine) {
    int count = 0;
    int inbtw = 0;

    for (int i = 0; text[i] != '\0'; i++) {

        if (text[i] == ' ') {

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

int main(int argc, char *argv[]) {

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
        return 0;
    }

    int fileWords[numFiles];
    
    for (int i = IndF; i < argc; i++) {

        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {

            printf("File named %s doesn't exist", argv[i]);
            return 0;

        }

        fseek(file, 0, SEEK_END); 
        long fileSize = ftell(file); 
        fseek(file, 0, SEEK_SET); 

        char *buffer = (char *)malloc(fileSize + 1); 
        if (buffer == NULL) {
            printf("File is empty\n");
            fclose(file);
            return 1;
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
            printf("File: %s --> Word count: %d\n", argv[i + IndF], fileWords[i]);
        }
    }

    return 0;
}
