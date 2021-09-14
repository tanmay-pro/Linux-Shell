// Created by tanmaypro on 11/09/21.
#include "../include/function_def.h"

char *trimString(char *startptr)
{
	while(isspace((unsigned char)*startptr)) {
		startptr++;
	}
	if(*startptr == 0){
		return startptr;
	}
	
	char *endptr;
	endptr = startptr + strlen(startptr) - 1;
	while(endptr > startptr && isspace((unsigned char)*endptr)) {
		endptr--;
	}
	endptr[1] = '\0';
	
	return startptr;
}

char* substr(const char *src, int m, int n)
{
	int len = n - m + 1;
	char *dest = (char*)malloc(sizeof(char) * (len + 1));
	strncpy(dest, (src + m), len);
	dest[len] = '\0';
	return dest;
}

char *remove_ws_middle(char *str)
{
	char *final = (char*)malloc(sizeof(char)* (strlen(str) + 1));
	int pos = 0;
	final[pos] = str[0];
	pos++;
	for(int i = 1; i< strlen(str); i++)
	{
		if(str[i] == ' ' && str[i-1]== ' ')
		{
			;
		}
		else
		{
			final[pos] = str[i];
			pos++;
		}
	}
	final[pos] = '\0';
	return final;
}

int x_part_of_y(char *str1, char *str2)
{
	int set = 0;
	for(int i=1; i<= strlen(str2); i++)
	{
		if(strcmp(substr(str2, 0, i), str1) == 0)
		{
			set = 1;
			break;
		}
	}
	if(set)
		return 1;
	else
		return 0;
	
}