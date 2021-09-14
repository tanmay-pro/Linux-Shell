// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

void pwd_func()
{
	char curPath[max_path_size];
	getcwd(curPath, max_path_size);
	printf("%s\n", curPath);
}