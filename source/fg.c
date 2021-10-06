#include "../include/function_def.h"

void convert_fg(char *str, int *proc_size)
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
        printf("goyshell: fg: Invalid number of arguments\n");
        return;
    }

    int job = atoi(args[1]);

    for (int i = 0; i < *proc_size; i++)
    {
        if (proc[i].proc_id != -1)
        {
            if (job == proc[i].job_num)
            {
                pid_t pid = proc[i].proc_id;
                pid_t pid_shell = getpid();

                proc[i].proc_id = -1;

                signal(SIGTTOU, SIG_IGN);
                signal(SIGTTIN, SIG_IGN);
                tcsetpgrp(0, getpgid(pid));

                kill(pid, SIGCONT);
                int status;
                waitpid(pid, &status, WUNTRACED);
                tcsetpgrp(0, pid_shell);

                signal(SIGTTOU, SIG_DFL);
                signal(SIGTTIN, SIG_DFL);

                if (WIFSTOPPED(status))
                {
                    kill(pid, SIGSTOP);

                    proc[*proc_size].proc_id = pid;
                    strcpy(proc[*proc_size].proc_name, proc[i].proc_name);
                    proc[*proc_size].job_num = proc[i].job_num;
                    (*proc_size)++;
                }
                return;
            }
        }
    }

    printf("goyshell: fg: job not found: %d\n", job);
}