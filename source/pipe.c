#include "../include/function_def.h"
#include "../main.h"

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
    int pipes[2], new_fd = STDIN_FILENO; // pipes[] holds the file descriptors
    char *token, *saveptr = NULL;
    char cpy[strlen(str) + 1];
    strcpy(cpy, str);
    token = strtok_r(cpy, "|", &saveptr);
    while (token != NULL)
    {
        strcpy(prev, token);
        token = strtok_r(NULL, "|", &saveptr);
        int ret = pipe(pipes); // Create a one way communication between the two file desc
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
            dup2(new_fd, STDIN_FILENO); // System call for redirection of stdin to the file desc
            if (token != NULL)
            {
                dup2(pipes[1], STDOUT_FILENO); 
                // If there is another command, then the output of child should be input for the write end 
            }
            close(pipes[1]);
            int ret_val = redir_decider(prev, process_size);
            // To process each command independently, we perform fork.
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
            wait(&status); // wait for child to end
            close(pipes[1]);
            new_fd = pipes[0];
        }
    }
    close(new_fd);
}