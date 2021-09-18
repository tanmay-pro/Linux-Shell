// Created by tanmaypro on 9/15/21.
#include "../include/function_def.h"

void fg_bg_decider(char *str)
{
	char *trimmed_str;
	trimmed_str = trimString(str);
	if(trimmed_str[strlen(trimmed_str) - 1] == '&')
	{
		bg(substr(trimmed_str,0,(int)strlen(trimmed_str) - 2));
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
		char flags[max_number_flags][max_size_flags];
		char cpy[strlen(str) + 1];
		strcpy(cpy, str);
		token = strtok_r(cpy, " \t\n", &ptr);
		int count = 0;
		while(token != NULL)
		{
			strcpy(flags[count], token);
			count++;
			token = strtok_r(NULL, " \t\n", &ptr);
		}
		char *args[] = {token, *flags, NULL};
		int ret_val = execvp(args[0], args);
		if(ret_val == -1)
		{
			perror("Invalid Command"); // Or Printf: Command not found
			exit(1);
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		if(pid == -1) // On failure of fork statement
		{
			perror("Couldnt fork");
		}
		wait(NULL);
	}
}

void bg(char *str)
{
	int ppid = fork();
	if (ppid == 0)
	{
		char *ptr = NULL, *token, *token2;
		token = strtok_r(str, " \t\n", &ptr);
		token2 = strtok_r(NULL, " \t\n", &ptr);
		char *args[] = {token, token2, NULL};
		int ret_val = execvp(args[0], args);
		if(ret_val == -1)
		{
			perror("\nInvalid Command"); // Or Printf: Command not found
			exit(1);
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		if(ppid == -1) // On failure of fork statement
		{
			perror("\nCould not fork");
		}
		printf("%d\n", ppid);
	}
}