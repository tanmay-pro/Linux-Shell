#include "./include/function_def.h"
#include "main.h"

void zombie_handler()
{
	int status;
	int get = waitpid(-1, &status, WNOHANG); // Checks if any child process has changed its state
	// WNOHANG enables waitpid() to return immediately rather than waiting

	if (get > 0)  // Get has the process ID of the process which has exited
	{
		if (!WIFEXITED(status)) // Condition satisfied if the process has terminated abnormally
		{
			char print[max_process_name] = "";
			for (int i = 0; i < max_process_num; i++)
			{
				if (proc[i].proc_id == get)
				{
					proc[i].proc_id = -1;

					for (int j = 0; proc[i].proc_name[j] != '\0'; j++)
					{
						if (proc[i].proc_name[j] == ' ')
						{
							print[j] = '\0';
							break;
						}

						print[j] = proc[i].proc_name[j];
					}
				}
			}
			if (strcmp(print, "") == 0)
			{
				strcpy(print, "Process");
			}
			printf("%s with pid %d exited abnormally\n", print, get); 
			// Inform about abnormal exiting
		}
	}

	for (int i = 0; i < max_process_num; i++)
	{
		if (kill(proc[i].proc_id, 0) == -1) // The process has exited and does not exist anymore
		{
			char print[max_process_name] = "";
			for (int j = 0; proc[i].proc_name[j] != '\0'; j++)
			{
				if (proc[i].proc_name[j] == ' ')
				{
					print[j] = '\0';
					break;
				}

				print[j] = proc[i].proc_name[j];
			}

			if (strcmp(print, "") == 0)
			{
				strcpy(print, "Process");
			}
			printf("%s with pid %d exited normally\n", print, proc[i].proc_id);
			proc[i].proc_id = -1;
		}
	}
}

void null_func()
{
	;
}

char path[max_path_size]; // To Get Absolute path at any time
char home[max_path_size];
char *prev_des;
process proc[max_process_num];


int main()
{
	int number_of_commands = 0;
	printf("\033[2J\033[1;1H"); // To Clear Screen
	const char *username;
	const char *sysname;
	username = getUserName();
	sysname = getSysName();
	getcwd(home, max_path_size);
	prev_des = (char *)calloc(max_path_size, sizeof(char));
	prev_des[0] = '\0';
	int process_num = 0;

	for (int i = 0; i < max_process_num; i++)
	{
		proc[i].proc_id = -1;
	}
	while (1)
	{
		signal(SIGINT, null_func); // Change the default behaviour of ctrl+C to not close the shell
		signal(SIGTSTP, null_func);  // Change the default behaviour of ctrl+Z issued by the user
		char *command = NULL, *ptr = NULL, *token;
		getcwd(path, max_path_size);
		strcpy(path, get_relative(path));
		printf("<%s@%s:%s> ", username, sysname, path);
		size_t comm_inp = 0;
		int return_check = getline(&command, &comm_inp, stdin); // Take input commands
		if (return_check == -1)
		{
			printf("goyshell: Error in taking command input\n");
			exit(1);
		} // If Error in taking command input
		token = strtok_r(command, "\n;", &ptr); 
		/* The input is first tokenized on semicolon and newline in
		order to allow multiple commands on a single line itself
		*/
		while (token != NULL)
		{
			char command_cpy[max_command_size];
			strcpy(command_cpy, token);
			char *command_part_ptr = NULL;
			char *command_part = strtok_r(command_cpy, " \t\n", &command_part_ptr); // Tokenize each command
			getcwd(path, max_path_size);
			strcpy(path, get_relative(path));
			if (strcmp(command_part, "replay") == 0 || strcmp(command_part, "repeat") == 0)
			{
				int exiter = decide_command(token, &process_num);
				if (!exiter)
				{
					exit(0);
				}
			}
			else
			{
				if (pipe_checker(token) == 1)
				{
					piping_func(token, &process_num);
				}
				else
				{
					int ret_val = redir_decider(token, &process_num);
					if (!ret_val)
					{
						int exiter = decide_command(token, &process_num);
						if (!exiter)
						{
							exit(0);
						}
					}
				}
			}
			token = strtok_r(NULL, "\n;", &ptr);
		}
		signal(SIGCHLD, null_func); // Change default behaviour when child process ends
		zombie_handler();
		free(command);
	}
	return 0;
}
