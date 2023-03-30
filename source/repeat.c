// Created by tanmaypro on 9/16/21.
#include "../include/function_def.h"
#include "../main.h"

void repeat(char *str, int *procsize)
{
	char *args[max_number_args];
	int count = tokenizer2(str, args, " \t\n");
	int numb = atoi(args[1]);
	char command[max_command_size];
	strcpy(command, substr(str, 8 + (int)strlen(args[1]), (int)strlen(str)));
	while (numb--)
	{
		if (pipe_checker(command) == 1)
		{
			piping_func(command, procsize);
		}
		else
		{
			int ret_val = redir_decider(command, procsize);
			if (!ret_val)
			{
				int exiter = decide_command(command, procsize);
				if (!exiter)
				{
					exit(0);
				}
			}
		}
	}
	return;
}
