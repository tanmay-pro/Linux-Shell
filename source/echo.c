// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

void echo_func(char *str)
{
	char *token, *saveptr = NULL;
	char args[max_number_args][max_size_args];
	int i = 0;
	token = strtok_r(str, " \t\n", &saveptr);
	while(token != NULL)
	{
		strcpy(args[i], token);
		i++;
		token = strtok_r(NULL, " \t\n", &saveptr);
	}
	for(int j = 1; j < i; j++)
	{
		printf("%s ", args[j]);
	}
	printf("\n");
}