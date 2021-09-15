// Created by tanmaypro on 9/14/21.
#include "../include/function_def.h"

void ls_decider(char *str)
{
	char *nstr = (char *)malloc(sizeof(char)*(strlen(str) + 3));
	strcpy(nstr , str);
	strcat(nstr, " ");
	const char* ch1 = " -a ";
	const char* ch2 = " -l ";
	const char* ch3 = " -al ";
	const char* ch4 = " -la ";
	
	char *c1, *c2, *c3, *c4;
	c1 = strstr(nstr, ch1);
	c2 = strstr(nstr, ch2);
	c3 = strstr(nstr, ch3);
	c4 = strstr(nstr, ch4);
	
	if(c3 != NULL || c4 != NULL || c1 != NULL && c2 != NULL )
	{
		ls_al(str);
	}
	else if(c1 != NULL)
	{
		ls_a(str);
	}
	else if(c2 != NULL)
	{
		ls_l(str);
	}
	else
	{
		ls(str);
	}
}

void ls_a(char *str)
{
	printf("Hello1\n");
}
void ls_l(char *str)
{
	printf("Hello2\n");
}
void ls_al(char *str)
{
	printf("Hello3\n");
}
void ls(char *str)
{
	char final_path[max_path_size];
	char *token, *ptr = NULL;
	token = strtok_r(str, " \t\n", &ptr);
	int num_of_args = 0;
	int set = 1;
	while(token != NULL)
	{
		num_of_args++;
		if(num_of_args > 1)
		{
			printf("Invalid Command\n");
			set = 0;
			break;
		}
		token = strtok_r(NULL, " \t\n", &ptr);
		if(token == NULL)
		{
			strcpy(final_path, home);
		}
		else if(token[0] == '~')
		{
			char *newpath;
			newpath = (char*)malloc(sizeof(char) * (max_path_size));
			strcpy(newpath, home);
			strcat(newpath, token + 1);
			strcpy(final_path, newpath);
		}
		else
		{
			strcpy(final_path, token);
		}
	}
	if(set)
	{
		DIR *dir;
		struct dirent* diret;
		dir = opendir(final_path);
		if(!dir)
		{
			perror(final_path);
		}
		else
		{
			while((diret = readdir(dir))!= NULL)
			{
				struct stat buf;
				char *name_of_file = diret->d_name;
				if(name_of_file[0] != '.')
				{
					printf("%s\n", name_of_file);
				}
			}
		}
	}
	
}