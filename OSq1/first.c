#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        
        printf("fork failed\n");
        return 1; 
    }
    else if (rc == 0)
    {
        
        printf("Child is having ID <%d>\n", (int)getpid());
        printf("My Parent ID is <%d>\n", (int)getppid());
    }
    else
    {
        
        printf("Parent (P) is having ID <%d>\n",(int)getpid());

        int status;
        wait(&status); 

        printf("ID of P's Child is <%d>\n",rc);
    }
    return 0;
}
