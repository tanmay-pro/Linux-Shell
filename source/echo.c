// Created by tanmaypro on 12/09/21.
#include "../include/function_def.h"

void echo_func(char str[])
{
	char *final_str;
	final_str = substr(str, 5, (int)strlen(str));
	char *trimmed_str;
	trimmed_str = trimString(final_str);
	char *final_ans = remove_ws_middle(trimmed_str);
	printf("%s\n", final_ans);
}