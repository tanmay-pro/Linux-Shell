#ifndef GOYSHELL_JOBS_H
#define GOYSHELL_JOBS_H
#include "function_def.h"

typedef struct printprc
{

    int job_num;
    char name[max_process_name];
    pid_t pid;
    char status;

} printprc;

void jobs(char *str, int *proc_size, char character); // Location: jobs.c // Function: Implement jobs function
void sort_jobs(printprc *stopped, int n); // Location: jobs.c // Function: Sort jobs according to job number and then name

#endif
