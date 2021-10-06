#include "../include/function_def.h"

void output_redir(char *file_name, char *str, int *proc_count, char ch)
{
    int orig_fd;
    int new_fd;
    if (ch == 'f')
        new_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        new_fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (new_fd == -1)
    {
        perror("open ");
        return;
    }
    orig_fd = dup(STDOUT_FILENO);
    if (dup2(new_fd, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        return;
    }
    int exiter = decide_command(str, proc_count);
    if (!exiter)
    {
        exit(0);
    }
    dup2(orig_fd, STDOUT_FILENO);
    close(new_fd);
    return;
}

void input_redir(char *file_name, char *str, int *proc_count)
{
    int new_fd;
    int orig_fd;
    new_fd = open(file_name, O_RDONLY);
    if (new_fd == -1)
    {
        printf("goyshell: %s: No such file or directory\n", file_name);
        return;
    }
    orig_fd = dup(STDIN_FILENO);
    if (dup2(new_fd, STDIN_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        return;
    }
    int exiter = decide_command(str, proc_count);
    if (!exiter)
    {
        exit(0);
    }
    dup2(orig_fd, STDIN_FILENO);
    close(new_fd);
    return;
}

void input_output_redir(char *file_in, char *file_out, char *str, int *proc_count, char ch)
{
    int orig_in_fd, new_in_fd;
    int orig_out_fd, new_out_fd;
    new_in_fd = open(file_in, O_RDONLY);
    if (new_in_fd == -1)
    {
        printf("goyshell: %s: No such file or directory\n", file_in);
        return;
    }
    if (ch == 'f')
        new_out_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        new_out_fd = open(file_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (new_out_fd == -1)
    {
        perror("open");
    }
    orig_in_fd = dup(STDIN_FILENO);
    if (dup2(new_in_fd, STDIN_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        return;
    }
    orig_out_fd = dup(STDOUT_FILENO);
    if (dup2(new_out_fd, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        return;
    }
    int exiter = decide_command(str, proc_count);
    if (!exiter)
    {
        exit(0);
    }
    close(new_in_fd);
    close(new_out_fd);
    dup2(orig_out_fd, STDOUT_FILENO);
    dup2(orig_in_fd, STDIN_FILENO);

    return;
}

int redir_decider(char *str, int *proc_count)
{
    char cpy[strlen(str) + 1];
    strcpy(cpy, str);
    char args[max_number_args][max_size_args];
    for (int i = max_number_args - 1; i >= 0; i--)
    {
        strcpy(args[i], "\0");
    }
    char *ptr = NULL, *token;
    token = strtok_r(cpy, " \n\t", &ptr);
    int i = 0;
    int append_check = 0;
    int set_in = 0, set_out = 0, pos_in = -1, pos_out = -1;
    while (token != NULL)
    {
        strcpy(args[i], token);
        i++;
        if (strcmp(token, ">") == 0)
        {
            set_out = 1;
            pos_out = i;
        }
        else if (strcmp(token, "<") == 0)
        {
            set_in = 1;
            pos_in = i;
        }
        else if (strcmp(token, ">>") == 0)
        {
            set_out = 1;
            pos_out = i;
            append_check = 1;
        }
        token = strtok_r(NULL, " \n\t", &ptr);
    }
    if (set_in == 1 && set_out == 1)
    {
        if (args[pos_in] == NULL || args[pos_out] == NULL)
        {
            printf("goyshell: syntax error near unexpected token `newline'\n");
            return 1;
        }
        char new_str[max_command_size] = "\0";
        for (int i = 0; i < max_number_args; i++)
        {
            if (strcmp(args[i], "") == 0)
            {
                break;
            }
            else
            {
                if ((i != pos_in) && (i != pos_out) && (i != pos_in - 1) && (i != pos_out - 1))
                {
                    strcat(new_str, args[i]);
                    strcat(new_str, " ");
                }
            }
        }
        if (append_check == 1)
            input_output_redir(args[pos_in], args[pos_out], new_str, proc_count, 't');
        else
            input_output_redir(args[pos_in], args[pos_out], new_str, proc_count, 'f');
        return 1;
    }
    else if (set_in == 1)
    {
        if (args[pos_in] == NULL)
        {
            printf("goyshell: syntax error near unexpected token `newline'\n");
            return 1;
        }
        char new_str[max_command_size] = "\0";
        for (int i = 0; i < max_number_args; i++)
        {
            if (strcmp(args[i], "") == 0)
            {
                break;
            }
            else
            {
                if ((i != pos_in) && (i != pos_in - 1))
                {
                    strcat(new_str, args[i]);
                    strcat(new_str, " ");
                }
            }
        }
        input_redir(args[pos_in], new_str, proc_count);
        return 1;
    }
    else if (set_out == 1)
    {
        if (args[pos_out] == NULL)
        {
            printf("goyshell: syntax error near unexpected token `newline'\n");
            return 1;
        }
        char new_str[max_command_size] = "\0";
        for (int i = 0; i < max_number_args; i++)
        {
            if (strcmp(args[i], "") == 0)
            {
                break;
            }
            else
            {
                if ((i != pos_out) && (i != pos_out - 1))
                {
                    strcat(new_str, args[i]);
                    strcat(new_str, " ");
                }
            }
        }
        if (append_check == 1)
            output_redir(args[pos_out], new_str, proc_count, 't');
        else
            output_redir(args[pos_out], new_str, proc_count, 'f');
        return 1;
    }
    else
    {
        return 0;
    }
}