// Created by tanmaypro on 9/15/21.
#include "../include/function_def.h"
#include "../main.h"

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
		fg(str, proce);
	}
}

void fg(char *str, int *max_proc)
{
	int pid = fork();
	if (pid == 0)
	{
		setpgid(0, 0);
		char *args[max_number_args];
		int count = tokenizer2(str, args, " \t\n");
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
		waitpid(temp, &status, WUNTRACED); // Wait for child process to finish
		tcsetpgrp(0, getpgid(shellPid));
		signal(SIGTTOU, SIG_DFL);
		signal(SIGTTIN, SIG_DFL); // Resume back to default execution

		if (WIFSTOPPED(status)) // To handle ctrl + Z
		{
			kill(pid, SIGSTOP);

			proc[*max_proc].proc_id = pid;
			strcpy(proc[*max_proc].proc_name, str);
			proc[*max_proc].job_num = *max_proc + 1;
			(*max_proc)++;
		}
	}
}

void bg(char *str, int *max_proc)
{
	int pid = fork();
	if (pid == 0)
	{
		setpgid(0, 0);
		char *args[max_number_args];
		int count = tokenizer2(str, args, " \t\n");
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
		proc[*max_proc].proc_id = pid;
		strcpy(proc[*max_proc].proc_name, str);
		proc[*max_proc].job_num = (*max_proc) + 1;
		(*max_proc)++;
	}
}