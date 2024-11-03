# Linux Shell

Linux Shell implemented in C

## Usage

1. make
2. ./goyshell

To delete the binary file, run `make clean`.

## Assumptions

* In ls -l command, I am converting the modified time to modified year if the file is > 6 months old from the time the program is run.
* Maximum size of any path = 2000 characters
* Maximum number of arguments + flags in any command = 20
* Maximum size of any argument/flag = 100 characters
* Maximum size of name of any process = 2000 characters
* Maximum number of backgrund processes run in one instance of shell = 100
* Maximum size of any Command = 2000 characters

## File Structure

### source

* bg.c
  * Contains convert_bg() function which changes the state of a stopped background job to running (in the background). The shell throws an error if there exists no background job corresponding to the given job number. Also, the shell does nothing if the job is already running in the background.  

* cd.c
  * Contains cd() function which implements the change directory command. It considers all possible cases of:
    * change the current working directory to the relative or the absolute path passed as argument.
    * `~` to go back to the shell executable directory.
    * `..` to go to the previous directory.
    * `-` will change your directory to the previous directory you were in.
    * no arguements passed change the directory to home directory

* commander.c
  * Contains decide_command() function which helps us in deciding which command should be executed depending on the input. Let us say ls is the input, then it should run the function ls().
  * The function returns 0 in case the program needs to be exited via either the quit command or the exit command.
  * Else the command returns 1.

* echo.c
  * It performs the echo command similar to bash while ignoring single or double quotes.
  * The only function it contains is the echo_func().

* fg_bg.c
  * It contains the fg_bg_decider function to decide whether the command supposed to be run in fg or in bg depdening on whether the tokenized command contains an & character at end or not.
  * It contains the fg() function which basically forks and creates a child process. The child process is further used to do execvp command whereas the parent is suppsoed to wait till the child process finishes.
  * It contains the bg() function which basically forks and creates a child process. The child process is further used to do execvp command whereas the parent is also executing simultaneoulsy. It does not wait for the child.

* fg.c
  * It contains the convert_fg() function which brings a running or stopped background job corresponding to given job number, to the foreground, and changes it's state to running. Goyshell throws an error if no job with the given job number exists.

* jobs.c
  * It contains the jobs_decider function() which decides which version of jobs is to be executed if it is a valid jobs command. It covers the following possibilities:
    * jobs
    * jobs -r
    * jobs -s
    * jobs -r -s
    * jobs -s -r
  * It contains the jobs command which runs the appropriate jobs version and displays all relevant bacground processes with their process ids.
  * It contains the sort_jobs() command which sorts the jobs according to name and then by number (in case command name is same).

* ls.c
  * It contains the ls_decider function which desides whether the ls command is of type:
    * ls
    * ls -a
    * ls -l
    * ls -a -l or ls -al and so on...
  * The above is implemented using strstr function searching for a needle in hayscak (figuratively).
  * It contains individual functions to implement the above possibilities.  
  * Features:
    * Lists the contents of the given directory.
    * Add `-l` to display the details of each file.
    * Add `-a` to display the hidden contents.
    * The directories and flags can be mentioned in any order after ls

* pinfo.c
  * This executes the procss information command.
  * It contains only one function named pinfo().
  * It extracts data from various files of /proc/pid/ and gives output of type:
    * process id
    * process status
    * memory
    * Executable path
  * If the PID is not mentioned it will show the information about the shell process.

* pipe.c
  * It contains the pipe_checker() function which detects whether the input command has a pipe or not by tokenizing input.
  * It contains the piping_function() command which performs piping redirection operation using pipe() (which creates a unidirectional data channel that can be used for interprocess communication).

* prompt.c
  * This file contains the functions of getting the user name and getting the host name.
  * These functions are called only once at the beginning, when the program is executed.
  
* pwd.c
  * This c file contains only the pwd fucntion.
  * It displays the absolute path of present working directory.

* repeat.c
  * It contains only the repeat function which repeats a particular command by pasing the command multiple times through command_decider.

* replay.c
  * It contains the replay_func() which repeats a particular command multiple times in certain intervals depending on the given frequency.

* sig.c
  * It performs the sig() function which takes the job number of a running job and sends the signal corresponding to signal number to that process.

* string_func.c
  * It contains the following functions:
    * trimString(): This function basically trims a string of characters.
    * substr(): This function gets the substring of the string passed as the first argument depedning on the values of the second and third arguments.
    * remove_ws_middle(): This function removes all spaces from middle and leaves just one space instead. This was required for executing the echo function.
    * x_part_of_y(): This checks whether the string x is a prefix of the string y.

### include

* function_def.h
  * Contains all the files to be included
  * Contains all function definitions
  * Contains all global varaibles
  * Contains all Max Size # defines determining max sizes of variables across the program.\
  * Contains structs used throughout the program.

* jobs.h
  * Contains definition of struct required for printing while performing jobs operation
  * Contaibs function definitions of sort_jobs and jobs functions.

### main.c

* Contains the main function which calls the decider_command function to decide which function is required to be executed on the basis of input.
* It contains the zombie handler function
* All the input lines are tokenized using strtok_r considering all arguments and multiple commands in single line if separated by semicolon.
* You can run more than 1 shell command in  a single line by separating them with a `;`.

### main.h

* Contains global variables in extern form.
* Contains few Max Size # defines determining max sizes of variables across the program.
