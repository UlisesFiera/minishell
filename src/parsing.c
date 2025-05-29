/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:40:35 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/09 13:40:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *command, int index)
{
	char	*env_var;
	int		i;
	int		j;
	int		size;

	size = 0;
	i = index + 1;
	while (command[i] && ((command[i] >= 'A' && command[i] <= 'Z') || (command[i] >= 'a' && command[i] <= 'z') || (command[i] >= '0' && command[i] <= '9') || command[i] == '_'))
	{
		size++;
		i++;
	}
	env_var = malloc(sizeof(char) * (size + 1));
	env_var[size] = '\0';
	i = index + 1;
	j = 0;
	while (command[i] && ((command[i] >= 'A' && command[i] <= 'Z') || (command[i] >= 'a' && command[i] <= 'z') || (command[i] >= '0' && command[i] <= '9') || command[i] == '_'))
	{
		env_var[j] = command[i];
		i++;
		j++;
	}
	return (env_var);
}

char	*env_cleaner(char *executable, char **env, t_gen_data *data, char *full_exec) // must free
{
	char	*name;
	char	*path;
	char	*sufix;
	char	*prefix;
	char	*final_env;
	char	*prev_final;
	int		i;
	int		j;
	int		index;
	int		exit_status;

	if (*executable == '?')
	{
		exit_status = WIFEXITED(data->exit_status);
		final_env = ft_itoa(exit_status);
		return (final_env);
	}
	i = 0;
	if (executable[i] >= '0' && executable[i] <= '9')
	{
		i++;
		j = i;
		while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') || (executable[i] >= 'a' && executable[i] <= 'z') || (executable[i] >= '0' && executable[i] <= '9') || executable[i] == '_'))
			i++;
		sufix = malloc(sizeof(char) * (i + 1));
		sufix[i] = '\0';
		i = 0;
		while (sufix[i])
		{
			sufix[i] = executable[j];
			i++;
			j++;
		}
		i = 0;
		while (full_exec[i] != '$')
			i++;
		prefix = malloc(sizeof(char) * (i + 1));
		prefix[i] = '\0';
		final_env = ft_strjoin(prefix, sufix);
		return (final_env);
	}
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') || (executable[i] >= 'a' && executable[i] <= 'z') || (executable[i] >= '0' && executable[i] <= '9') || executable[i] == '_'))
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') || (executable[i] >= 'a' && executable[i] <= 'z') || (executable[i] >= '0' && executable[i] <= '9') || executable[i] == '_'))
	{
		name[i] = executable[i];
		i++;
	}
	name[i] = '\0';
	path = ft_getenv(name, env);
	if (!path)
	{
		sufix = malloc(1);
		sufix[0] = '\0';
		i = 0;
		while (full_exec[i] != '$')
			i++;
		prefix = malloc(sizeof(char) * (i + 1));
		prefix[i] = '\0';
		final_env = ft_strjoin(prefix, sufix);
		return (final_env);
	}
	j = 0;
	index = i;
	while (executable[i])
	{
		i++;
		j++;
	}
	i = 0;
	sufix = malloc(sizeof(char) * (j + 1));
	while (executable[index])
	{
		sufix[i] = executable[index];
		index++;
		i++;
	}
	sufix[i] = '\0';
	prev_final = ft_strjoin(path, sufix);
	i = 0;
	while (full_exec[i] != '$')
		i++;
	prefix = malloc(sizeof(char) * (i + 1));
	prefix[i] = '\0';
	final_env = ft_strjoin(prefix, prev_final);
	return (final_env);
}

void	parse_env_vars_quotes(t_gen_data *data, char **env, char *command, int index)
{
	int		count;
	int		i;
	int		j;
	char	**env_paths;
	char	*new_string;

	count = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '$')
			count++;
		i++;
	}
	if (count == 0)
		return ;
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] == '$')
		{
			env_paths[j] = env_cleaner(command + i + 1, env, data, command);
			new_string = ft_strinsert(command, env_paths[j], i, 1);
			command = new_string;
			j++;
		}
		i++;
	}
	free(data->executables[index]);
	data->executables[index] = command;
}

void	parse_env_vars(t_gen_data *data, char **env) // must free env paths
{
	int		count;
	int		i;
	int		j;
	int		n;
	char	**env_paths;

	count = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->quotes[i] == 1)
			parse_env_vars_quotes(data, env, data->executables[i], i);
		else if (data->quotes[i] != 2)
		{
			j = 0;
			while(data->executables[i][j])
			{
				if (data->executables[i][j] == '$')
					count++;
				j++;
			}
		}
		i++;
	}
	if (count == 0)
		return ;
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	i = 0;
	j = 0;
	while (data->executables[i])
	{
		n = 0;
		while (data->executables[i][n])
		{
			if (data->executables[i][n] == '$')
			{
				env_paths[j] = env_cleaner(data->executables[i] + n + 1, env, data, data->executables[i]);
				free(data->executables[i]);
				data->executables[i] = env_paths[j];
				j++;
			}
			n++;
		}
		i++;
	}
}

void	set_pipe_flag(t_gen_data *data)
{
	int	i;

	i = 0;
	while (data->executables[i])
	{
		if (!strcmp(data->executables[i], "|"))
			data->pipe_flag++;
		i++;
	}
}

void	parse_input(t_gen_data *data, char **env)
{
	int		exec_count;
	int		index;
	int		i;

	exec_count = exec_counter(data->input);
	data->executables = malloc(sizeof(char *) * (exec_count + 1));
	if (!data->executables)
		return ;
	data->executables[exec_count] = NULL;
	init_quotes(data, exec_count);
	index = 0;
	i = 0;
	while (i < exec_count)
	{
		data->executables[i] = exec_split(data->input, &index, i, data);
		i++;
	}
	parse_env_vars(data, env);
	set_pipe_flag(data);
}
