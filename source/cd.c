// Created by tanmaypro on 13/09/21.
#include "../include/function_def.h"
#include "../main.h"

void cd(char *str)
{
	char *args[max_number_args];
	int count = tokenizer2(str, args, " \t\n");
	if (count > 2)
	{
		printf("goyshell: cd: too many arguments\n");
		return;
	}
	char nstr[strlen(str) + 1];
	strcpy(nstr, str);
	char *token, *ptr = NULL;
	token = strtok_r(nstr, " \t\n", &ptr);
	token = strtok_r(NULL, " \t\n", &ptr);
	if (token == NULL)
	{
		char temp_path[max_path_size];
		getcwd(temp_path, max_path_size);
		chdir(home);
		strcpy(prev_des, temp_path);
	}
	else if (token[0] == '~')
	{
		char *newpath;
		newpath = (char *)malloc(sizeof(char) * (max_path_size));
		strcpy(newpath, home);
		strcat(newpath, token + 1);
		char temp_path[max_path_size];
		getcwd(temp_path, max_path_size);
		int ret_val = chdir(newpath);
		if (ret_val < 0)
		{
			printf("goyshell: cd: %s: No such file or directory\n", token);
		}
		else
		{
			strcpy(prev_des, temp_path);
		}
	}
	else if (token[0] == '-')
	{
		if (prev_des[0] == '\0')
		{
			printf("goyshell: cd: OLDPWD not set\n");
			return;
		}
		char temp_path[max_path_size];
		getcwd(temp_path, max_path_size);

		int ret_val = chdir(prev_des);
		if (ret_val < 0)
		{
			printf("goyshell: cd: %s: No such file or directory\n", token);
		}
		else
		{
			char curPath[max_path_size];
			getcwd(curPath, max_path_size);
			strcpy(curPath, get_relative(curPath));
			printf("%s\n", curPath);
			strcpy(prev_des, temp_path);
		}
	}
	else
	{
		char temp_path[max_path_size];
		getcwd(temp_path, max_path_size);
		int ret_val = chdir(token);
		if (ret_val < 0)
		{
			printf("goyshell: cd: %s: No such file or directory\n", token);
		}
		else
		{
			strcpy(prev_des, temp_path);
		}
	}
}
