#include "shell_functions.h"

/**
 * get_custom_environment - returns the string array copy of our environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_custom_environment(info_t *info)
{
		if (!info->environ || info->env_changed)
		{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
		}

		return (info->environ);
}

/**
 * remove_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int remove_environment_variable(info_t *info, char *var)
{
		list_t *node = info->env;
		size_t i = 0;
		char *p;

		if (!node || !var)
		return (0);

		while (node)
		{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
		info->env_changed = delete_node_at_index(&(info->env), i);
		i = 0;
		node = info->env;
		continue;
		}
		node = node->next;
		i++;
		}
		return (info->env_changed);
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int set_environment_variable(info_t *info, char *var, char *value)
{
		char *buf = NULL;
		list_t *node;
		char *p;

		if (!var || !value)
		return (0);

		buf = malloc(_strlen(var) + _strlen(value) + 2);
		if (!buf)
		return (1);
		_strcpy(buf, var);
		_strcat(buf, "=");
		_strcat(buf, value);
		node = info->env;
		while (node)
		{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
		free(node->str);
		node->str = buf;
		info->env_changed = 1;
		return (0);
		}
		node = node->next;
		}
		add_node_end(&(info->env), buf, 0);
		free(buf);
		info->env_changed = 1;
		return (0);
}
