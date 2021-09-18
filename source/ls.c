// Created by tanmaypro on 9/14/21.
#include "../include/function_def.h"

void ls_decider(char *str)
{
	char *nstr = (char *)malloc(sizeof(char)*(strlen(str) + 3));
	strcpy(nstr , str);
	strcat(nstr, " ");
	const char* ch1 = " -a ";
	const char* ch2 = " -l ";
	const char* ch3 = " -al ";
	const char* ch4 = " -la ";
	
	char *c1, *c2, *c3, *c4;
	c1 = strstr(nstr, ch1);
	c2 = strstr(nstr, ch2);
	c3 = strstr(nstr, ch3);
	c4 = strstr(nstr, ch4);
	
	if(c3 != NULL || c4 != NULL || (c1 != NULL && c2 != NULL))
	{
		ls_al(str);
	}
	else if(c1 != NULL)
	{
		ls_a(str);
	}
	else if(c2 != NULL)
	{
		ls_l(str);
	}
	else
	{
		ls(str);
	}
}

void ls_a(char *str)
{
	char final_path[max_path_size];
	char *token, *ptr = NULL;
	token = strtok_r(str, " \t\n", &ptr);
	int c = 0;
	while(token != NULL)
	{
		token = strtok_r(NULL, " \t\n", &ptr);
		if(token != NULL && strcmp(token, "-a") == 0)
		{
			continue;
		}
		else
		{
			c++;
		}
		if(token == NULL && c ==1)
		{
			char curPath[max_path_size];
			getcwd(curPath, max_path_size);
			strcpy(final_path, curPath);
		}
		else if(token == NULL && c > 1)
		{
			break;
		}
		else if(token[0] == '~')
		{
			char *newpath;
			newpath = (char*)malloc(sizeof(char) * (max_path_size));
			strcpy(newpath, home);
			strcat(newpath, token + 1);
			strcpy(final_path, newpath);
		}
		else
		{
			strcpy(final_path, token);
		}
		DIR *dir;
		struct dirent* diret;
		dir = opendir(final_path);
		if(!dir)
		{
			perror(final_path);
		}
		else
		{
			while((diret = readdir(dir))!= NULL)
			{
				struct stat buf;
				char *name_of_file = diret->d_name;
				printf("%s\n", name_of_file);
				
			}
		}
	}
}

void ls_l(char *str)
{
	char final_path[max_path_size];
	char *token, *ptr = NULL;
	token = strtok_r(str, " \t\n", &ptr);
	int c = 0;
	while(token != NULL)
	{
		token = strtok_r(NULL, " \t\n", &ptr);
		if(token != NULL && strcmp(token, "-l") == 0)
		{
			continue;
		}
		else
		{
			c++;
		}
		if(token == NULL && c ==1)
		{
			char curPath[max_path_size];
			getcwd(curPath, max_path_size);
			strcpy(final_path, curPath);
		}
		else if(token == NULL && c > 1)
		{
			break;
		}
		else if(token[0] == '~')
		{
			char *newpath;
			newpath = (char*)malloc(sizeof(char) * (max_path_size));
			strcpy(newpath, home);
			strcat(newpath, token + 1);
			strcpy(final_path, newpath);
		}
		else
		{
			strcpy(final_path, token);
		}
		DIR *dir;
		char date[max_date_size];
		struct tm *x;
		struct dirent* diret;
		long long net_sum = 0;
		dir = opendir(final_path);
		if(!dir)
		{
			perror(final_path);
			return;
		}
		while((diret = readdir(dir)) != NULL)
		{
			char *name_of_file = diret->d_name;
			char curPath[max_path_size];
			
			strcpy(curPath, final_path);
			strcat(curPath, "/\0");
			strcat(curPath, name_of_file);
			
			struct stat buf;
			stat(curPath, &buf);
			if(name_of_file[0] != '.')
			{
				net_sum += buf.st_blocks;
			}
		}
		printf("total %lld\n", net_sum/2);
		closedir(dir);
		dir = opendir(final_path);
		while((diret = readdir(dir))!= NULL)
		{
			char *name_of_file = diret->d_name;
			if(name_of_file[0] == '.')
			{
				continue;
			}
			char *path_for_stat = (char *)malloc(sizeof(char) * max_path_size);
			path[0] = '\0';
			strcpy(path_for_stat, final_path);
			strcat(path_for_stat, "/\0");
			strcat(path_for_stat, name_of_file);
			struct stat buf;
			stat(path_for_stat, &buf);
//			if(ret < 0)
//			{
//				perror("goyshell: ls");
//				return;
//			}
			int permission_types[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
			char permission_chars[3] = {'r', 'w', 'x'};
			char permission_print[11];
			permission_print[10] = '\0';
			
			if(S_ISDIR(buf.st_mode)) // check if it is a directory or file
			{
				permission_print[0] = 'd';
			}
			else
			{
				permission_print[0] = '-';
			}
			for(int i = 0; i < 9; i++)
			{
				if(buf.st_mode & permission_types[i])
				{
					int p = i % 3;
					permission_print[i+1] = permission_chars[p];
				}
				else{
					permission_print[i+1] = '-';
				}
			}
			permission_print[10] = '\0';
			
			char *modtime = (char *)malloc(20);
			strftime(modtime, 20, "%b %e %H:%M", localtime(&buf.st_mtime));
			
			printf("%s %d %s %s ", permission_print, (int)buf.st_nlink, (getgrgid(buf.st_gid))->gr_name, (getpwuid(buf.st_uid))->pw_name);
			//if() // year check
			printf("%ld %s %s\n", buf.st_size, modtime, name_of_file);
		}
		
	}
}

void ls_al(char *str)
{
	char final_path[max_path_size];
	char *token, *ptr = NULL;
	token = strtok_r(str, " \t\n", &ptr);
	int c = 0;
	while(token != NULL)
	{
		token = strtok_r(NULL, " \t\n", &ptr);
		if((token != NULL && strcmp(token, "-a") == 0) || (token != NULL && strcmp(token, "-l") == 0) || (token != NULL && strcmp(token, "-al") == 0) || (token != NULL && strcmp(token, "-la") == 0))
		{
			continue;
		}
		else
		{
			c++;
		}
		if(token == NULL && c == 1)
		{
			char curPath[max_path_size];
			getcwd(curPath, max_path_size);
			strcpy(final_path, curPath);
		}
		else if(token == NULL && c > 1)
		{
			break;
		}
		else if(token[0] == '~')
		{
			char *newpath;
			newpath = (char*)malloc(sizeof(char) * (max_path_size));
			strcpy(newpath, home);
			strcat(newpath, token + 1);
			strcpy(final_path, newpath);
		}
		else
		{
			strcpy(final_path, token);
		}
		DIR *dir;
		char date[max_date_size];
		struct dirent* diret;
		struct stat statistics;
		long long net_sum = 0;
		dir = opendir(final_path);
		if(!dir)
		{
			perror(final_path);
			return;
		}
		while((diret = readdir(dir)) != NULL)
		{
			char *name_of_file = diret->d_name;
			char curPath[max_path_size];
			
			strcpy(curPath, final_path);
			strcat(curPath, "/\0");
			strcat(curPath, name_of_file);
			
			struct stat buf;
			int ret = stat(curPath, &buf);
//			if(ret < 0)
//			{
//				perror("goyshell: ls");
//				return;
//			}
			net_sum += buf.st_blocks;
		}
		printf("total %lld\n", net_sum/2);
		closedir(dir);
		dir = opendir(final_path);
		while((diret = readdir(dir))!= NULL)
		{
			char *name_of_file = diret->d_name;
			char *path_for_stat = (char *)malloc(sizeof(char) * max_path_size);
			path[0] = '\0';
			strcpy(path_for_stat, final_path);
			strcat(path_for_stat, "/\0");
			strcat(path_for_stat, name_of_file);
			struct stat buf;
			int ret = stat(path_for_stat, &buf);
//			if(ret < 0)
//			{
//				perror("goyshell: ls");
//				return;
//			}
			
			int permission_types[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
			char permission_chars[3] = {'r', 'w', 'x'};
			char permission_print[11];
			permission_print[10] = '\0';
			
			if(S_ISDIR(buf.st_mode)) // check if it is a directory or file
			{
				permission_print[0] = 'd';
			}
			else
			{
				permission_print[0] = '-';
			}
			for(int i = 0; i < 9; i++)
			{
				if(buf.st_mode & permission_types[i])
				{
					int p = i % 3;
					permission_print[i+1] = permission_chars[p];
				}
				else{
					permission_print[i+1] = '-';
				}
			}
			permission_print[10] = '\0';
			
			char *modtime = (char *)malloc(20);
			strftime(modtime, 20, "%b %e %H:%M", localtime(&buf.st_mtime));
			
			printf("%s %d %s %s ", permission_print, (int)buf.st_nlink, (getgrgid(buf.st_gid))->gr_name, (getpwuid(buf.st_uid))->pw_name);
			printf("%ld %s %s\n", buf.st_size, modtime, name_of_file);
		}
		
	}
}

void ls(char *str)
{
	char final_path[max_path_size];
	char *token, *ptr = NULL;
	token = strtok_r(str, " \t\n", &ptr);
	int c = 0;
	while(token != NULL)
	{
		token = strtok_r(NULL, " \t\n", &ptr);
		c++;
		if(token == NULL && c ==1)
		{
			char curPath[max_path_size];
			getcwd(curPath, max_path_size);
			strcpy(final_path, curPath);
		}
		else if(token == NULL && c > 1)
		{
			break;
		}
		else if(token[0] == '~')
		{
			char *newpath;
			newpath = (char*)malloc(sizeof(char) * (max_path_size));
			strcpy(newpath, home);
			strcat(newpath, token + 1);
			strcpy(final_path, newpath);
		}
		else
		{
			strcpy(final_path, token);
		}
		DIR *dir;
		struct dirent* diret;
		dir = opendir(final_path);
		if(!dir)
		{
			perror(final_path);
		}
		else
		{
			while((diret = readdir(dir))!= NULL)
			{
				struct stat buf;
				char *name_of_file = diret->d_name;
				if(name_of_file[0] != '.')
				{
					printf("%s\n", name_of_file);
				}
			}
		}
	}
}