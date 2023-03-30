#ifndef MAIN_H_
#define MAIN_H_

#define max_path_size 2000
#define max_process_num 100
#define max_process_name 2000

typedef struct process
{
	int proc_id;
	char proc_name[max_process_name];
	int job_num;
} process;

extern char path[max_path_size]; // To Get Absolute path at any time
extern char home[max_path_size];
extern char *prev_des;
extern process proc[max_process_num];


#endif