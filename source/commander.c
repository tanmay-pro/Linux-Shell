// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

int decide_command(char *str, int *process_num)
{
	char cpy[strlen(str) + 1];
	strcpy(cpy, str);
	char *token, *saveptr = NULL;
	token = strtok_r(cpy, " \t\n", &saveptr);

	if (strcmp(token, "echo") == 0)
	{
		echo_func(str);
	}
	else if (strcmp(token, "pwd") == 0)
	{
		pwd_func();
	}
	else if (strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0)
	{
		signal(SIGCHLD, null_func);
		zombie_handler();
		return 0;
	}
	else if (strcmp(token, "cd") == 0)
	{
		cd(str);
	}
	else if (strcmp(token, "ls") == 0)
	{
		ls_decider(str);
	}
	else if (strcmp(token, "repeat") == 0)
	{
		repeat(str, process_num);
	}
	else if (strcmp(token, "pinfo") == 0)
	{
		pinfo(str);
	}
	else if (strcmp(token, "jobs") == 0)
	{
		jobs_decider(str, process_num);
	}
	else if (strcmp(token, "sig") == 0)
	{
		sig(str, process_num);
	}
	else if(strcmp(token, "fg") == 0)
	{
		convert_fg(str, process_num);
	}
	else if (strcmp(token, "bg") == 0)
	{
		convert_bg(str, process_num);
	}
	else
	{
		fg_bg_decider(str, process_num);
	}
	return 1;
}