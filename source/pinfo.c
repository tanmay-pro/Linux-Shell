// Created by tanmaypro on 9/17/21.

#include "../include/function_def.h"

void pinfo(char *str)
{
	char generate[max_size] = "/proc/";
	char cpy[strlen(str) + 1];
	strcpy(cpy, str);
	int arg_counter = 0;
	char *token , *saveptr = NULL;
	token = strtok_r(cpy, " \t\n", &saveptr);
	while (token != NULL)
	{
		arg_counter++;
		token = strtok_r(NULL, " \t\n", &saveptr);
	}
	pid_t pid = getpid();
	if(arg_counter > 2)
	{
		printf("bash: pinfo: invalid number of arguments\n");
		return;
	}
	else if(arg_counter == 2)
	{
		token = strtok_r(str, " \t\n", &saveptr);
		token = strtok_r(NULL, " \t\n", &saveptr);
		pid = atoi(token);
	}
	sprintf(generate, "/proc/%d/", pid);
	char path_status[max_path_size];
	path_status[0] = '\0';
	strcpy(path_status, generate);
	strcat(path_status, "stat");
	
	FILE *fp = fopen(path_status, "r");
	
	if(fp == NULL)
	{
		printf("bash: pinfo: No process with pid: %d\n", pid);
		return;
	}
	else
	{
		char a[max_size], b[max_size], t[max_size];
		fscanf(fp, "%s %s %s", a, b, t);
		printf("pid -- %d\n", pid);
		printf("Process Status -- %s\n", t);
	}
	
	char path_vm[max_path_size];
	path_vm[0] = '\0';
	strcpy(path_vm, generate);
	strcat(path_vm, "statm");
	
	FILE *fp2 = fopen(path_vm, "r");
	
	if(fp2 == NULL)
	{
		printf("bash: pinfo: No process with pid: %d\n", pid);
		return;
	}
	else
	{
		char a[max_size];
		fscanf(fp2, "%s", a);
		printf("memory -- %s {Virtual Memory}\n", a);
	}
	
	char path_rest[max_size];
	strcpy(path_rest, generate);
	strcat(path_rest, "exe");
	
	char path_execute[max_size];
	int ret_val = readlink(path_rest, path_execute, max_size - 1);
	if(ret_val == -1)
	{
		printf("bash: pinfo: Executable path couldn't be accessed");
		return;
	}
	path_execute[ret_val] = '\0';
	
	char temp[max_path_size];
	temp[0] = '~';
	temp[1] = '\0';
	if(x_part_of_y(home, path_execute))
	{
		strcpy(path_execute, strcat(temp, substr(path_execute, (int)strlen(home), (int)strlen(path_execute))));
	}
	printf("Executable Path -- %s\n", path_execute);
}