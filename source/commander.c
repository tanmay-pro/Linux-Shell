// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

int decide_command(char *str)
{
	char cpy[strlen(str) + 1];
	strcpy(cpy, str);
	char *token , *saveptr = NULL;
	token = strtok_r(cpy, " \t", &saveptr);

	if(strcmp(token, "echo") == 0)
	{
		echo_func(str);
		return 1;
	}
	else if(strcmp(token, "pwd") == 0)
	{
		pwd_func();
		return 1;
	}
	else if(strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0)
	{
		return 0;
	}
	else if(strcmp(token, "cd") == 0)
	{
		cd(str);
		return 1;
	}
	else if(strcmp(token, "ls") == 0)
	{
		ls_decider(str);
		return 1;
	}
	return 0;
}