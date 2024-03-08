#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fibonacci(int n) {
    if (n <= 0) {
        return;
    }

    int fib_table[n + 1];
    fib_table[0] = 0;
    fib_table[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib_table[i] = fib_table[i - 1] + fib_table[i - 2];
    }

    printf("Fibonacci sequence up to %d:", n);
    for (int i = 0; i <= n; i++) {
        printf(" %d\n", fib_table[i]);
    }
    printf("\n");
}

int factorial(int n) {
    int result = 1;
    
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    
    return result;
}


int main(int argc, char *argv[])
{
    int rc = vfork();
    if (rc < 0)
    {
        
        printf("fork failed\n");
        return 1; 
    }
    else if (rc == 0) //child process
    {
        int answer = factorial(4);  
        printf("The factorial of 4 is : %d\n", answer);      
    }
    else // parent process
    {
        fibonacci(16);
        
    }
    return 0;
}
