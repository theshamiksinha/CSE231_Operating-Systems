#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    if (argc == 3)
    {

        if (strcmp(argv[1], "-v") == 0)
        {
            // -v vala case

            if (mkdir(argv[2], 0777) == -1)
            {
                printf("Error: Directory already exists\n");
                return 0;
            }
            else
            {
                printf("Directory created: %s\n", argv[2]);
            }

            if (chdir(argv[2]) == -1)
            {
                perror("Error changing directory\n");
                return 0;
            }
            else
            {
                printf("Directory changed to %s successfully!\n", argv[2]);
                char path[1000];
                if (getcwd(path, sizeof(path)) != NULL)
                {
                    printf("Current working directory is %s\n", path);
                }
            }
        }
        else if (strcmp(argv[1], "-r") == 0)
        {
            // -r vala case

            if (access(argv[2], F_OK) == 0)
            {
                printf("directory already existed ,removing directory..\n");
                rmdir(argv[2]);

                printf("making directory after removal \n");
                mkdir(argv[2], 0777);
                chdir(argv[2]);

                char path[4096];
                if (getcwd(path, sizeof(path)) != NULL)
                {
                    printf("Current working directory is %s\n", path);
                }
            }

            else
            {
                printf("directory did not exist\n");
                mkdir(argv[2], 0777);
                printf("changing directory to %s\n", argv[2]);
                chdir(argv[2]);

                char path[1000];
                if (getcwd(path, sizeof(path)) != NULL)
                {
                    printf("Current working directory is %s\n", path);
                }
            }
        }
        else if (argc == 2)
        {
            if (mkdir(argv[2], 0777) == -1)
            {
                printf("Error: Directory already exists\n");
                return 0;
            }
            else
            {
                printf("Directory created: %s\n", argv[2]);
            }

            if (chdir(argv[2]) == -1)
            {
                perror("Error changing directory\n");
                return 0;
            }
            else
            {
                printf("Directory changed to %s successfully!\n", argv[2]);
                char path[1000];
                if (getcwd(path, sizeof(path)) != NULL)
                {
                    printf("Current working directory is %s\n", path);
                }
            }
        }
        else
        {
            printf("Error in command input");
        }

        
    }

    return 0;
}