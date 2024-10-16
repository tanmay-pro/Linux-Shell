#include "../include/function_def.h"
#include "../main.h"

void sig(char *str, int *proc_size)
{
    char *args[max_number_args];
    int count = tokenizer2(str, args, " \t\n");
    if (count > 3)
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
                if (kill(proc[i].proc_id, sig_number) < 0) // Send a signal to some particular job
                {
                    printf("goyshell: sig: kill: %s\n", strerror(errno));
                }
                return;
            }
        }
    }
    printf("goyshell: sig: No such job\n");
    return;
}