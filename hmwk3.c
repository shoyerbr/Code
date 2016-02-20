#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int calc_2(char oper, int num1, int num2)
{
    if (oper == '+')
        return num1 + num2;
    if (oper == '-')
        return num1 - num2;
    if (oper == '*')
        return num1 * num2;
    if (oper == '/')
        return num1 / num2;
    return 0;
}

int calc_3(char oper, int num1, int num2, int num3)
{
    if (oper == '+')
        return num1 + num2 + num3;
    if (oper == '-')
        return num1 - num2 - num3;
    if (oper == '*')
        return num1 * num2 * num3;
    if (oper == '/')
        return num1 / num2 / num3;
    return 0;
}

int main (int argc, char* argv[])
{
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int rc_1 = pipe(pipe1);
    int rc_2 = pipe(pipe2);
    int rc_3 = pipe(pipe3);
    FILE * file;
    if (rc_1 == -1 || rc_2 == -1 || rc_3 == -1)
    {
        perror("pipe failed");
        return EXIT_FAILURE;
    }
    if (argc != 2)
    {
        perror("argument error");
        return EXIT_FAILURE;
    }
    file = fopen (argv[1], "r");
    pid_t pid;
    char line[999];
    int simple[999];
    simple[0] = 0;
    int temp = 0;
    int stop = 0;
    int number_count = 0;
    while (fscanf(file, "%s", line) != EOF)
    {
       int len;
       stop = 0;
       for (len = 0; len < strlen(line); len++)
        {
            int num = line[len];
            if (num != 40 && num != 41 )
            {
                if (num == 42 || num == 43 || num == 45 || num == 47)
                {
                    simple[temp] = num + 1000;
                    printf("%d\n", simple[temp]);
                    temp++;
                }
                else
                {
                    if (stop == 0)
                    {
                        simple[temp] = atoi(line);
                        number_count++;
                        printf("%d\n", simple[temp]);
                        stop = 1;
                    }
                    temp++;
                }
            }
        }
    }
    pid_t original_pid = getpid();
    int running_total = 0;
    int first_pid = 1;
    int which_pipe = 1;
    while (1)
    {
        if (first_pid == 1)
        {
             int i;
             for (i = 0; i < number_count; i++)
            {
                pid = fork();
                if (pid == 0)
                {
                    which_pipe = i + 1;
                    i = number_count;
                }
            }
        }
        
        if (pid == -1)
        {
            perror("fork failed\n");
            return EXIT_FAILURE;
        }
        if(pid == 0)
        {
            return EXIT_SUCCESS;
        }
        else
            pid = fork();
        if (getpid() == original_pid)
        {
            perror("done");
            return EXIT_FAILURE;
            break;
        }
    }
    printf("%s\n", line);
    fscanf(file, "%s", line);
    return EXIT_SUCCESS;
}