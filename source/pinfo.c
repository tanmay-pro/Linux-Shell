// Created by tanmaypro on 9/17/21.
#include "../main.h"
#include "../include/function_def.h"

void pinfo(char *str)
{
	char generate[max_size] = "/proc/";
	char *args[max_number_args];
	int arg_counter = tokenizer2(str, args, " \t\n");
	pid_t pid = getpid();
	if (arg_counter > 2)
	{
		printf("goyshell: pinfo: invalid number of arguments\n");
		return;
	}
	else if (arg_counter == 2)
	{
		pid = atoi(args[1]);
	}
	sprintf(generate, "/proc/%d/", pid);
	char path_status[max_path_size];
	path_status[0] = '\0';
	strcpy(path_status, generate);
	strcat(path_status, "stat");

	FILE *fp = fopen(path_status, "r");

	if (fp == NULL)
	{
		printf("goyshell: pinfo: No process with pid: %d\n", pid);
		return;
	}
	else
	{
		char a[max_size], t[max_size];
		fscanf(fp, "%s %s %s", a, a, t);
		printf("pid -- %d\n", pid);
		if (getpgid(pid) == pid)
		{
			printf("Process Status -- %s+\n", t);
		}
		else
			printf("Process Status -- %s\n", t);
	}

	char path_vm[max_path_size];
	path_vm[0] = '\0';
	strcpy(path_vm, generate);
	strcat(path_vm, "statm");

	FILE *fp2 = fopen(path_vm, "r");

	if (fp2 == NULL)
	{
		printf("goyshell: pinfo: No process with pid: %d\n", pid);
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
	if (ret_val == -1)
	{
		printf("goyshell: pinfo: Executable path couldn't be accessed");
		return;
	}
	path_execute[ret_val] = '\0';
	strcpy(path_execute, get_relative(path_execute));
	printf("Executable Path -- %s\n", path_execute);
}