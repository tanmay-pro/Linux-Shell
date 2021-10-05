#include "../include/function_def.h"

void sig(char *str, int *proc_size)
{
    char nstr[strlen(str) + 1];
    strcpy(nstr, str);
    char *token, *saveptr = NULL;
    token = strtok_r(nstr, " \t\n", &saveptr);
    int c = 0;
    char args[max_number_args][max_size_args];
    while (token != NULL)
    {
        strcpy(args[c], token);
        c++;
        token = strtok_r(NULL, " \t\n", &saveptr);
    }
    if (c > 3)
    {
        printf("goyshell: sig: Invalid number of arguments\n");
        return;
    }
    int job_number = atoi(args[1]);
    int sig_number = atoi(args[2]);
    for (int i = 0; i < *proc_size; i++)
    {
        if (proc[i].proc_id != -1)
        {
            if (proc[i].job_num == job_number)
            {
                if (kill(proc[i].proc_id, sig_number) < 0)
                {
                    printf("goyshell: sig: kill: %s\n", strerror(errno));
                }
                return;
            }
            return;
        }
    }
    printf("goyshell: sig: No such job\n");
    return;
}