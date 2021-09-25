// Created by tanmaypro on 11/09/21.
#include "../include/function_def.h"

const char *getUserName()
{
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw)
	{
		return pw->pw_name;
	}
	return NULL;
}

const char *getSysName()
{
	char *hostbuffer;
	hostbuffer = (char *)malloc(256 * sizeof(char));
	hostbuffer[255] = '\0';
	int return_val = gethostname(hostbuffer, 255);
	if (return_val == 0)
	{
		return hostbuffer;
	}
	else
	{
		perror("Error in Getting Host name");
		exit(1);
	}
}
