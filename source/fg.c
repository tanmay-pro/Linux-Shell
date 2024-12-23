#include "../include/function_def.h"
#include "../main.h"

void convert_fg(char *str, int *proc_size) // To move a process to the foreground
{
    char *args[max_number_args];
    int count = tokenizer2(str, args, " \t\n");
    if (count > 2)
    {
        printf("goyshell: fg: Invalid number of arguments\n");
        return;
    }

    int job = atoi(args[1]);

    for (int i = 0; i < (*proc_size); i++)
    {
        if (proc[i].proc_id != -1)
        {
            if (job == proc[i].job_num)
            {
                pid_t pid = proc[i].proc_id;
                pid_t pid_shell = getpid();

                proc[i].proc_id = -1;
                // Mechanics similar to creation of a fg process
                signal(SIGTTOU, SIG_IGN);
                signal(SIGTTIN, SIG_IGN); // To prevent background processes from interferring with the foreground process
                tcsetpgrp(0, getpgid(pid));

                kill(pid, SIGCONT); // Continue the execution of the process using SIGCONT
                int status;
                waitpid(pid, &status, WUNTRACED);
                tcsetpgrp(0, pid_shell);

                signal(SIGTTOU, SIG_DFL);
                signal(SIGTTIN, SIG_DFL); // Resume back to default execution

                if (WIFSTOPPED(status))
                {
                    // To handle stopped processes later on as bg processes
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