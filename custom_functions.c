#include "shell_functions.h"

/**
 * my_custom_exit - exits the shell
 * @my_info: Structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * 
 * Return: exits with a given exit status
 * (0) if my_info->args[0] != "exit"
 */
int my_custom_exit(info_t *my_info) {
	 int exit_check;

	if (my_info->args[1]) {
	exit_check = atoi(my_info->args[1]);
	if (exit_check == 0 && my_info->args[1][0] != '0') {
	 my_info->error_number = 2;
	return 1;
	}
	my_info->error_number = exit_check;
	return -2;
	}
	my_info->error_number = -1;
	return -2;
}
/**
 * my_custom_cd - changes the current directory of the process
 * @my_info: Structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * 
 * Return: Always 0
 */
int my_custom_cd(info_t *my_info) {
	char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
	my_info->error_number = 1;

	if (!my_info->args[1]) {
	new_dir = getenv("HOME");
	if (!new_dir)
	chdir_result = chdir((new_dir = getenv("PWD")) ? new_dir : "/");
	else
	 chdir_result = chdir(new_dir);
	} else if (strcmp(my_info->args[1], "-") == 0) {
	if (!getenv("OLDPWD")) {
	 my_info->error_number = 1;
	return 1;
	 }
	chdir_result = chdir((new_dir = getenv("OLDPWD")) ? new_dir : "/");
	} else {
	chdir_result = chdir(my_info->args[1]);
	}

	if (chdir_result == -1) {
	my_info->error_number = 1;
	 } else {
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", getcwd(buffer, 1024), 1);
    }

	 return 0;
}
/**
 * my_custom_help - provides help information (not yet implemented)
 * @my_info: Structure containing potential arguments.
 *	Used to maintain a constant function prototype.
 * 
 * Return: Always 0
 */
int my_custom_help(info_t *my_info) {
	char **arg_array;

	arg_array = my_info->args;

	if (!arg_array || !arg_array[0])
	{
	 return (0);
	 }
	return (0);
}
