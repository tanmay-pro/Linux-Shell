#include "./include/function_def.h"
int main() {
	
	printf("\033[2J\033[1;1H"); // To Clear Screen
	const char *username;
	const char *sysname;
	username = getUserName();
	sysname = getSysName();
	
	getcwd(home, max_path_size);
	
	char *command = NULL, *ptr = NULL, *token;
	char delim[] = "\n;";
	
	while(1)
	{
		getcwd(path, max_path_size);
		
		char temp[max_path_size];
		temp[0] = '~';
		temp[1] = '\0';
		if(x_part_of_y(home, path))
		{
			strcpy(path, strcat(temp, substr(path, (int)strlen(home), (int)strlen(path))));
		} // To Get Relative path if it is above in directory order
		
		printf("<%s@%s:%s> ", username, sysname, path);
		
		size_t comm_inp = 0;
		int return_check = getline(&command, &comm_inp, stdin); // Take input commands
		if(return_check == -1)
		{
			printf("Error in taking command input\n");
			exit(1);
		} // If Error in taking command input
		
		token = strtok_r(command, delim, &ptr);
		int set = 1;
		while(token != NULL)
		{
			getcwd(path, max_path_size);
			
			char temp2[max_path_size];
			temp2[0] = '~';
			temp2[1] = '\0';
			if(x_part_of_y(home, path))
			{
				strcpy(path, strcat(temp2, substr(path, (int)strlen(home), (int)strlen(path))));
			} // To Get Relative path if it is above in directory order
			int exiter = decide_command(token);
			if(!exiter)
			{
				set = 0;
				break;
			}
			token = strtok_r(NULL, delim, &ptr);
		}
		free(command);
		if(set == 0)
		{
			break;
		}
	}
	return 0;
}
