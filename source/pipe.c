#include "../include/function_def.h"

int pipe_checker(char *str)
{
    char *args[max_number_args];
    int arg_counter = tokenizer2(str, args, " \t\n");
    for (int i = 0; i < arg_counter; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            return 1;
        }
    }
    return 0;
}

void piping_func(char *str, int *process_size)
{
    char *prev = (char *)malloc(max_command_size);
    int pipes[2], new_fd = STDIN_FILENO;
    char *token, *saveptr = NULL;
    token = strtok_r(str, "|", &saveptr);
    while (token != NULL)
    {
        strcpy(prev, token);
        token = strtok_r(NULL, "|", &saveptr);
        int ret = pipe(pipes);
        if (ret < 0)
        {
            perror("goyshell: Piping");
            return;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("goyshell: Piping pid < 0");
            return;
        }
        if (pid == 0)
        {
            close(pipes[0]);
            dup2(new_fd, STDIN_FILENO); //take input from prvout (initially stdin)
            if (token != NULL)
            {                                  //if another piped process after it
                dup2(pipes[1], STDOUT_FILENO); //all output to pipe-writeend (otherwise to stdout)
            }
            close(pipes[1]); //closing the FD, not the file (stored in STDOUT now)
            int ret_val = redir_decider(prev, process_size);
            if (!ret_val)
            {
                int exiter = decide_command(prev, process_size);
                if (!exiter)
                {
                    exit(0);
                }
            }
            exit(0);
        }
        else
        {
            int status = 0;
            wait(&status); //wait for child to end
            close(pipes[1]);
            new_fd = pipes[0];
        }
    }
    close(new_fd);
}