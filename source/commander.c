// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

int decide_command(char *str)
{
	if(strcmp(substr(str, 0, 4), "echo") == 0)
	{
		echo_func(str);
		return 1;
	}
	else if(strcmp(substr(str, 0, 4), "exit") == 0 || strcmp(substr(str, 0, 4), "quit") == 0)
	{
		return 0;
	}
}