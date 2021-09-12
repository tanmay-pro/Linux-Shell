#include "./include/function_def.h"
int main() {
	
	const char *username;
	const char *sysname;
	username = getUserName();
	sysname = getSysName();
	
	while(1)
	{
		char *path; // To Get Absolute path at any time
		
		path = (char*)malloc(max_path_size * sizeof(char));
		getcwd(path, max_path_size);
		
		printf("<%s@%s:%s> ", username, sysname, path);
		
		char *command;
		size_t comm_inp = 0;
		int return_check = getline(&command, &comm_inp, stdin); // Take input commands
		if(return_check == -1)
		{
			printf("Error in taking command input\n");
			exit(1);
		} // If Error in taking command input
		
		char *command_trim;
		command_trim = trimString(command);
		int exiter = decide_command(command_trim);
		if(exiter == 0)
		{
			break;
		}
	}
	return 0;
}
