// Created by tanmaypro on 9/16/21.
#include "../include/function_def.h"

void repeat(char *str, int *procsize)
{
	char cpy[strlen(str) + 1];
	strcpy(cpy, str);
	char *token , *saveptr = NULL;
	token = strtok_r(cpy, " \t\n", &saveptr);
	token = strtok_r(NULL, " \t\n", &saveptr);
	int numb = atoi(token);
	while(numb--)
	{
		int exiter = decide_command(substr(str, 8 + (int)strlen(token), (int)strlen(str)), procsize);
		if (!exiter)
		{
			exit(0);
		}
	}
}
