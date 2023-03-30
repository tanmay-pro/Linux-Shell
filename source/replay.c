#include "../include/function_def.h"
#include "../main.h"


void replay_func(char *str, int *proc_size)
{
    char *args[max_number_args];
    int count = tokenizer2(str, args, " \t\n");
    char command[max_command_size];
    strcpy(command, "\0");
    int pos_i = -1;
    int pos_p = -1;
    int pos_c = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(args[i], "-interval") == 0)
        {
            pos_i = i;
        }
        else if (strcmp(args[i], "-period") == 0)
        {
            pos_p = i;
        }
        else if (strcmp(args[i], "-command") == 0)
        {
            pos_c = i;
        }
    }
    printf("pos_i = %d\n", pos_i);
    printf("pos_p = %d\n", pos_p);
    printf("pos_c = %d\n", pos_c);
    if (pos_i == -1 || pos_p == -1 || pos_c == -1)
    {
        printf("goyshell: replay: missing arguments\n");
        return;
    }
    if (pos_i < pos_p && pos_c < pos_i)
    {
        for (int i = pos_c + 1; i < pos_i; i++)
        {
            strcat(command, args[i]);
            strcat(command, " ");
        }
    }
    else if (pos_p < pos_i && pos_c < pos_p)
    {
        for (int i = pos_p + 1; i < pos_i; i++)
        {
            strcat(command, args[i]);
            strcat(command, " ");
        }
    }
    else if (pos_p > pos_c && pos_c > pos_i)
    {
        for (int i = pos_c + 1; i < pos_p; i++)
        {
            strcat(command, args[i]);
            strcat(command, " ");
        }
    }
    else if (pos_i > pos_c && pos_c > pos_p)
    {
        for (int i = pos_c + 1; i < pos_i; i++)
        {
            strcat(command, args[i]);
            strcat(command, " ");
        }
    }
    else
    {
        for (int i = pos_c + 1; i < count; i++)
        {
            strcat(command, args[i]);
            strcat(command, " ");
        }
    }
    int interval = atoi(args[pos_i + 1]);
    int period = atoi(args[pos_p + 1]);
    int freq = period / interval;
    int dur = 0;
    while (freq--)
    {
        sleep(interval);
        dur += interval;
        if (pipe_checker(command) == 1)
        {
            piping_func(command, proc_size);
        }
        else
        {
            int ret_val = redir_decider(command, proc_size);
            if (!ret_val)
            {
                int exiter = decide_command(command, proc_size);
                if (!exiter)
                {
                    exit(0);
                }
            }
        }
    }
    if (dur < period)
    {
        sleep(period - dur);
    }
    return;
}