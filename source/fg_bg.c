// Created by tanmaypro on 9/15/21.
#include "../include/function_def.h"

void fg_bg_decider(char *str, int *proce)
{
	char *trimmed_str;
	trimmed_str = trimString(str);
	if (trimmed_str[strlen(trimmed_str) - 1] == '&')
	{
		bg(substr(trimmed_str, 0, (int)strlen(trimmed_str) - 2), proce);
	}
	else
	{
		fg(str);
	}
}

void fg(char *str)
{
	int pid = fork();
	if (pid == 0)
	{
		setpgid(0, 0);
		char *ptr = NULL, *token;
		char *args[max_number_args];
		int i;
		for (i = 0; i < max_number_args; i++)
		{
			args[i] = (char *)malloc(sizeof(char) * max_size_args);
		}
		char cpy[strlen(str) + 1];
		strcpy(cpy, str);
		token = strtok_r(cpy, " \t\n", &ptr);
		int count = 0;
		while (token != NULL)
		{
			strcpy(args[count], token);
			count++;
			token = strtok_r(NULL, " \t\n", &ptr);
		}
		args[count] = NULL;
		int ret_val = execvp(args[0], args);
		if (ret_val == -1)
		{
			printf("%s: command not found\n", args[0]);
			exit(1);
		}
	}
	else
	{
		int temp = pid;
		int shellPid = getpid();
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTTIN, SIG_IGN); // To prevent background processes from interferring with the foreground process
		tcsetpgrp(0, pid);
		int status;
		waitpid(temp, &status, WUNTRACED); // Wait for the child process to finish
		tcsetpgrp(0, getpgid(shellPid));
		signal(SIGTTOU, SIG_DFL);
		signal(SIGTTIN, SIG_DFL); // Resume back to default execution

		// if (WIFSTOPPED(status))
		// {
		//     kill(pid, SIGSTOP);

		//     proc[*proc_size].proc_id = pid;
		//     strcpy(proc[*proc_size].name, proc[i].name);
		//     (*proc_size)++;
		// }
	}
}

void bg(char *str, int *process_num)
{
	int pid = fork();
	if (pid == 0)
	{
		setpgid(0, 0);
		char *ptr = NULL, *token;
		char *args[max_number_args];
		int i;
		for (i = 0; i < max_number_args; i++)
		{
			args[i] = (char *)malloc(sizeof(char) * max_size_args);
		}
		char cpy[strlen(str) + 1];
		strcpy(cpy, str);
		token = strtok_r(cpy, " \t\n", &ptr);
		int count = 0;
		while (token != NULL)
		{
			strcpy(args[count], token);
			count++;
			token = strtok_r(NULL, " \t\n", &ptr);
		}
		args[count] = NULL;
		int ret_val = execvp(args[0], args);
		if (ret_val == -1)
		{
			printf("%s: command not found\n", args[0]);
			exit(1);
		}
	}
	else
	{
		setpgid(pid, pid);
		if (pid == -1) // On failure of fork statement
		{
			perror("Couldnt fork");
			return;
		}
		printf("%d\n", pid);
		proc[*process_num].proc_id = pid;
		strcpy(proc[*process_num].proc_name, str);
		proc[*process_num].job_num = (*process_num) + 1;
		(*process_num)++;
	}
}