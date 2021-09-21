// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

int decide_command(char *str, int *process_num)
{
	char cpy[strlen(str) + 1];
	strcpy(cpy, str);
	char *token , *saveptr = NULL;
	token = strtok_r(cpy, " \t\n", &saveptr);

	if(strcmp(token, "echo") == 0)
	{
		echo_func(str);
	}
	else if(strcmp(token, "pwd") == 0)
	{
		pwd_func();
	}
	else if(strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0)
	{
		signal(SIGCHLD, zom);
		return 0;
	}
	else if(strcmp(token, "cd") == 0)
	{
		cd(str);
	}
	else if(strcmp(token, "ls") == 0)
	{
		ls_decider(str);
	}
	else if(strcmp(token, "repeat") == 0)
	{
		repeat(str, process_num);
	}
	else if(strcmp(token, "pinfo") == 0)
	{
		pinfo(str);
	}
	else
	{
		fg_bg_decider(str, process_num);
	}
	signal(SIGCHLD, zom);
	return 1;
}