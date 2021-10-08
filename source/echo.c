// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

void echo_func(char *str)
{
	char *args[max_number_args];
	int count = tokenizer2(str, args, " \t\n");
	for(int j = 1; j < count; j++)
	{
		printf("%s ", args[j]);
	}
	printf("\n");
}