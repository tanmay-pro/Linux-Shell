#ifndef GOYSHELL_FUNCTION_DEF_H
#define GOYSHELL_FUNCTION_DEF_H

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <sys/resource.h>
#include <pwd.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/utsname.h>
#include <grp.h>

#define max_path_size 1000
#define max_number_args 10
#define max_size_args 100
#define max_process_name 1000
#define max_process_num 100
#define max_size 200
#define max_date_size 200

char path[max_path_size]; // To Get Absolute path at any time
char home[max_path_size];
char *prev_des;


typedef struct process
{
	int proc_id;
	char proc_name[max_process_name];
}process;

process proc[max_process_num];

const char *getUserName(); //Location: prompt.c // Function: To get Username of User
const char *getSysName(); //Location: prompt.c // Function: To get System Name
char *trimString(char *str); //Location: string_func.c // Function: To get Simplified Command after trimming
char* substr(const char *src, int m, int n); // Location: string_func.c // Function: To get substring of a string
void echo_func(char *str); //Location: echo.c // Function: Echo Command
int decide_command(char *str, int *process_num); //Location: commander.c // Function: Decide what to implement
char *remove_ws_middle(char* str); // Location: string_func.c // Function: remove all whitespaces from in between string and replace with one whitespace
void pwd_func(); // Location: pwd.c // Function: Print present working directory
int x_part_of_y(char *str1, char *str2); // Location: string_func.c // Function: Check if x is a substring of y from starting index 0
void cd(char *str); // Location: cd.c // Function: Perform change directory operation
void ls_decider(char *str); // Location: ls.c // Function: Perform ls operation
void ls_a(char *str);
void ls_l(char *str);
void ls_al(char *str);
void ls(char *str);
void fg(char *str);
void bg(char *str, int *proc_se);
void fg_bg_decider(char *str, int *proc_se);
void repeat(char *str, int *proc_se);
void pinfo(char *str);
void zom();

#endif
