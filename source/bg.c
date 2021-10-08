#include "../include/function_def.h"

void convert_bg(char *str, int *proc_size)
{
    char *args[max_number_args];
    int count = tokenizer2(str, args, " \t\n");

    if (count > 2)
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