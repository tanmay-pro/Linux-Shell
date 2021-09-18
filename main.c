#include "./include/function_def.h"
#include "./include/queue.h"
int main()
{
	int number_of_commands = 0;
	printf("\033[2J\033[1;1H"); // To Clear Screen
	const char *username;
	const char *sysname;
	username = getUserName();
	sysname = getSysName();
	ptrnode history;
	history = createnode("header");
	getcwd(home, max_path_size);
	prev_des = (char*)calloc(max_path_size, sizeof(char));
	prev_des[0] = '\0';
	while(1)
	{
		char *command = NULL, *ptr = NULL, *token;
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
		else
		{
			if(number_of_commands < 20)
			{
				push_front(history, command);
				number_of_commands++;
			}
			else
			{
				eject(history);
				push_front(history, command);
			}
			
		}
		
		token = strtok_r(command,  "\n;", &ptr);
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
				exit(0);
			}
			token = strtok_r(NULL,  "\n;", &ptr);
		}
		free(command);
	}
	return 0;
}
