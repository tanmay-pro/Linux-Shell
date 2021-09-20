// Created by tanmaypro on 9/15/21.
#include "../include/function_def.h"

void fg_bg_decider(char *str, int *proce)
{
	char *trimmed_str;
	trimmed_str = trimString(str);
	if(trimmed_str[strlen(trimmed_str) - 1] == '&')
	{
		bg(substr(trimmed_str,0,(int)strlen(trimmed_str) - 2), proce);
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
		char *ptr = NULL, *token;
		char *args[max_number_args];
		int i;
		for(i = 0; i < max_number_args; i++)
		{
			args[i] = (char *) malloc(sizeof(char) * max_size_args);
		}
		char cpy[strlen(str) + 1];
		strcpy(cpy, str);
		token = strtok_r(cpy, " \t\n", &ptr);
		int count = 0;
		while(token != NULL)
		{
			strcpy(args[count], token);
			count++;
			token = strtok_r(NULL, " \t\n", &ptr);
		}
		args[count] = NULL;
		int ret_val = execvp(args[0], args);
		if(ret_val == -1)
		{
			printf("%s: command not found\n", args[0]);
			exit(1);
		}
	}
	else
	{
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		if(pid == -1) // On failure of fork statement
		{
			perror("Couldnt fork");
			return;
		}
		wait(NULL);
	}
}

void bg(char *str, int *process_num)
{
	int pid = fork();
	if (pid == 0)
	{
		setpgid(0,0);
		char *ptr = NULL, *token;
		char *args[max_number_args];
		int i;
		for(i = 0; i < max_number_args; i++)
		{
			args[i] = (char *) malloc(sizeof(char) * max_size_args);
		}
		char cpy[strlen(str) + 1];
		strcpy(cpy, str);
		token = strtok_r(cpy, " \t\n", &ptr);
		int count = 0;
		while(token != NULL)
		{
			strcpy(args[count], token);
			count++;
			token = strtok_r(NULL, " \t\n", &ptr);
		}
		args[count] = NULL;
		int ret_val = execvp(args[0], args);
		if(ret_val == -1)
		{
			printf("%s: command not found\n", args[0]);
			exit(1);
		}
	}
	else
	{
		setpgid(pid, pid);
		if(pid == -1) // On failure of fork statement
		{
			perror("Couldnt fork");
			return;
		}
		printf("%d\n", pid);
		proc[*process_num].proc_id = pid;
		strcpy(proc[*process_num].proc_name, str);
		(*process_num)++;
	}
}