target:
	gcc -g main.c ./source/cd.c ./source/commander.c ./source/echo.c ./source/fg_bg.c ./source/ls.c ./source/pinfo.c ./source/prompt.c ./source/pwd.c ./source/repeat.c ./source/string_func.c ./source/redirection.c  ./source/jobs.c -o goyshell
clean:
	rm goyshell