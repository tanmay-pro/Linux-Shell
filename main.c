#include "./include/function_def.h"

void zom()
{
	int status;
	int get = waitpid(-1, &status, WNOHANG | WUNTRACED);
	
	if(get > 0)
	{
		if(!WIFEXITED(status))
		{
			char print[max_process_name] = "";
			for(int i = 0; i < max_process_num; i++)
			{
				if(proc[i].proc_id == get)
				{
					proc[i].proc_id = -1;
					
					for(int j = 0; proc[i].proc_name[j] != '\0'; j++)
					{
						if(proc[i].proc_name[j] == ' ')
						{
							print[j] = '\0';
							break;
						}
						
						print[j] = proc[i].proc_name[j];
					}
				}
			}
			if(strcmp(print, "") == 0)
			{
				strcpy(print, "Process");
			}
			printf("%s with pid %d exited abnormally\n", print, get);
		}
	}
	
	for(int i = 0; i < max_process_num; i++)
	{
		if(kill(proc[i].proc_id, 0) == -1)
		{
			char print[max_process_name] = "";
			for(int j = 0; proc[i].proc_name[j] != '\0'; j++)
			{
				if(proc[i].proc_name[j] == ' ')
				{
					print[j] = '\0';
					break;
				}
				
				print[j] = proc[i].proc_name[j];
			}
			
			if(strcmp(print, "") == 0)
			{
				strcpy(print, "Process");
			}
			printf("%s with pid %d exited normally\n", print, proc[i].proc_id);
			proc[i].proc_id = -1;
		}
	}
}

int main()
{
	int number_of_commands = 0;
	printf("\033[2J\033[1;1H"); // To Clear Screen
	const char *username;
	const char *sysname;
	username = getUserName();
	sysname = getSysName();
	getcwd(home, max_path_size);
	prev_des = (char*)calloc(max_path_size, sizeof(char));
	prev_des[0] = '\0';
	int process_num= 0;
	
	for(int i = 0; i < max_process_num; i++)
	{
		proc[i].proc_id = -1;
	}
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
			int exiter = decide_command(token, &process_num);
			if(!exiter)
			{
				exit(0);
			}
			token = strtok_r(NULL,  "\n;", &ptr);
		}
		signal(SIGCHLD, zom);
		free(command);
	}
	return 0;
}
