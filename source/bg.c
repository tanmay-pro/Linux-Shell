#include "../include/function_def.h"

void convert_bg(char *str, int *proc_size)
{
    char nstr[strlen(str) + 1];
    strcpy(nstr, str);
    char *token, *saveptr = NULL;
    token = strtok_r(nstr, " \t\n", &saveptr);
    char args[max_number_args][max_size_args];
    int c = 0;
    while (token != NULL)
    {
        strcpy(args[c], token);
        c++;
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    if (c > 2)
    {
        printf("goyshell: bg: Invalid number of arguments\n");
        return;
    }

    int job = atoi(args[1]);

    for (int i = 0; i < *proc_size; i++)
    {
        if (proc[i].proc_id != -1)
        {
            if (proc[i].job_num == job)
            {
                if (kill(proc[i].proc_id, SIGCONT) < 0)
                {
                    printf("goyshell: bg: Error in conversion\n");
                }
                return;
            }
        }
    }
    printf("goyshell: bg: job not found: %d\n", job);
}