#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void STRINGTime(const char *filename) {

    struct stat file_data;

    int check = stat(filename, &file_data);

    if (check == -1) {
        printf("Error STRINGTime / fault in file");
        return;
    }
    else{
        time_t real_time = file_data.st_mtime;

        struct tm *timeinfo;

        timeinfo = localtime(&real_time);

        char finalTime[100];

        strftime(finalTime, sizeof(finalTime), "%a %b %d %I:%M:%S %p", timeinfo);

        printf("%s IST %d\n", finalTime, timeinfo->tm_year + 1900);
    }
    
}

void RFCC(const char *filename) {

    struct stat file_data;
    
    int check = stat(filename, &file_data);

    if (check == -1) {
        printf("Error RRFC / fault in file");
        return;
    }
    else{
        char finalTime[100];  

        time_t real_time = file_data.st_mtime;

        struct tm *timeinfo;

        timeinfo = localtime(&real_time);
        
        strftime(finalTime, sizeof(finalTime), "%a, %d %b %Y %H:%M:%S ", timeinfo);

        printf("%s%s\n", finalTime, "+0530");
    }
}

int main(int argc, char *argv[]) {

    char *filename = NULL;

    if (argc > 3 || argc < 3) {
        
        printf("Arguments in command line not correct\n");
        
    }
    else if (argc == 3){

        if (strcmp(argv[1], "-d") == 0){

            // STRING
            filename = argv[2];
            STRINGTime(filename);
            
        } 
        else if (strcmp(argv[1], "-R") == 0) {

            // RFC
            filename = argv[2];
            RFCC(filename);
            
        }
        else{
            printf("Invalid option supplied\n");
        }

    }
    
    if (filename == NULL) {
        printf("No file name was given\n");
        return 0;
    }

    return 0;
}
