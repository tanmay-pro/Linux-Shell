// Created by tanmaypro on 13/09/21.
#include "../include/function_def.h"

void cd (char *str)
{
	char cpy[strlen(str) + 1];
	strcpy(cpy, str);
	int count = 0;
	char *tok, *saveptr = NULL;
	tok = strtok_r(cpy, " \t\n", &saveptr);
	while (tok != NULL)
	{
		count++;
		tok = strtok_r(NULL, " \t\n", &saveptr);
	}
	if(count > 2)
	{
		printf("bash: cd: too many arguments\n");
		return;
	}
	
	char *token, *ptr = NULL;
	token = strtok_r(str, " \t\n", &ptr);
	token = strtok_r(NULL, " \t\n", &ptr);
	if(token == NULL)
	{
		token = "~";
	}
	else if(token[0] == '~')
	{
		char *newpath;
		newpath = (char*)malloc(sizeof(char) * (max_path_size));
		strcpy(newpath, home);
		strcat(newpath, token + 1);
		char temp_path[max_path_size];
		getcwd(temp_path, max_path_size);
		int ret_val = chdir(newpath);
		if(ret_val < 0)
		{
			printf("bash: cd: %s: No such file or directory\n", token);
		}
		else
		{
			strcpy(prev_des, temp_path);
		}
	}
	else if(token[0] == '-')
	{
		if(prev_des[0] == '\0')
		{
			printf("bash: cd: OLDPWD not set\n");
			return;
		}
		char temp_path[max_path_size];
		getcwd(temp_path, max_path_size);
		
		int ret_val = chdir(prev_des);
		if(ret_val < 0)
		{
			printf("bash: cd: %s: No such file or directory\n", token);
		}
		else
		{
			char curPath[max_path_size];
			getcwd(curPath, max_path_size);
			char temp[max_path_size];
			temp[0] = '~';
			temp[1] = '\0';
			if(x_part_of_y(home, curPath))
			{
				strcpy(curPath, strcat(temp, substr(curPath, (int)strlen(home), (int)strlen(curPath))));
			}
			printf("%s\n", curPath);
			strcpy(prev_des, temp_path);
		}
	}
	else
	{
		char temp_path[max_path_size];
		getcwd(temp_path, max_path_size);
		int ret_val = chdir(token);
		if(ret_val < 0)
		{
			printf("bash: cd: %s: No such file or directory\n", token);
		}
		else
		{
			strcpy(prev_des, temp_path);
		}
	}
}
