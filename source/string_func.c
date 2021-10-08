// Created by tanmaypro on 11/09/21.
#include "../include/function_def.h"

char *trimString(char *startptr)
{
	while (isspace((unsigned char)*startptr))
	{
		startptr++;
	}
	if (*startptr == 0)
	{
		return startptr;
	}

	char *endptr;
	endptr = startptr + strlen(startptr) - 1;
	while (endptr > startptr && isspace((unsigned char)*endptr))
	{
		endptr--;
	}
	endptr[1] = '\0';

	return startptr;
}

char *substr(const char *src, int m, int n)
{
	int len = n - m + 1;
	char *dest = (char *)malloc(sizeof(char) * (len + 1));
	strncpy(dest, (src + m), len);
	dest[len] = '\0';
	return dest;
}

int x_part_of_y(char *str1, char *str2)
{
	int set = 0;
	for (int i = 1; i <= strlen(str2); i++)
	{
		if (strcmp(substr(str2, 0, i), str1) == 0)
		{
			set = 1;
			break;
		}
	}
	if (set)
		return 1;
	else
		return 0;
}

char *get_relative(char *str)
{
	char temp2[max_path_size];
	temp2[0] = '~';
	temp2[1] = '\0';
	if (x_part_of_y(home, str))
	{
		strcpy(str, strcat(temp2, substr(str, (int)strlen(home), (int)strlen(str))));
	} // To Get Relative path if it is above in directory order
	return str;
}

int tokenizer2(char *str, char *args[max_number_args], char *sep)
{
	char *ptr = NULL, *token;
	int i;
	for (i = 0; i < max_number_args; i++)
	{
		args[i] = (char *)malloc(sizeof(char) * max_size_args);
	}
	char cpy[strlen(str) + 1];
	strcpy(cpy, str);
	token = strtok_r(cpy, sep, &ptr);
	int count = 0;
	while (token != NULL)
	{
		strcpy(args[count], token);
		count++;
		token = strtok_r(NULL, sep, &ptr);
	}
	return count;
}
