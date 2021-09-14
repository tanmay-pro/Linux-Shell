// Created by tanmaypro on 13/09/21.
#include "../include/function_def.h"

void cd (char *str)
{
	char *token, *ptr = NULL;
	token = strtok_r(str, " \t\n", &ptr);
	token = strtok_r(NULL, " \t\n", &ptr);
	if(token == NULL)
	{
		token = "~";
	}
	if(token[0] == '~')
	{
		char *newpath;
		newpath = (char*)malloc(sizeof(char) * (max_path_size));
		strcpy(newpath, home);
		strcat(newpath, token + 1);
		int ret_val = chdir(newpath);
		if(ret_val < 0)
		{
			perror("Error in path");
		}
	}
	else
	{
		int ret_val = chdir(token);
		if(ret_val < 0)
		{
			perror("Error in path");
		}
	}
}
