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

#include "../minishell.h"

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
	char	*final_env;
	int		i;
	int		index;
	int		exit_status;

	(void)full_exec;
	if (*executable == '?')
	{
		exit_status = WEXITSTATUS(data->exit_status);
		final_env = ft_itoa(exit_status);
		return (final_env);
	}
	i = 0;
	if (executable[i] >= '0' && executable[i] <= '9')
	{
		while (executable[i] >= '0' && executable[i] <= '9')
			i++;
		index = i;
		while (executable[i] && executable[i] != ' ')
			i++;
		final_env = malloc(i);
		i = 0;
		while (executable[index] && executable[index] != ' ')
		{
			final_env[i] = executable[index];
			i++;
			index++;
		}
		return (final_env);
	}
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') || (executable[i] >= 'a' && executable[i] <= 'z') || (executable[i] >= '0' && executable[i] <= '9')))
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') || (executable[i] >= 'a' && executable[i] <= 'z') || (executable[i] >= '0' && executable[i] <= '9')))
	{
		name[i] = executable[i];
		i++;
	}
	name[i] = '\0';
	path = ft_getenv(name, env);
	if (!path)
	{
		path = malloc(2);
		path[0] = '\n';
		path[1] = '\0';
		return (path);
	}
	return (path);
}

void	parse_env_vars_quotes(t_gen_data *data, char **env, char *command, int index)
{
	char	*new_string;

	new_string = parse_env_vars(data, command, env);
	free(data->executables[index]);
	data->executables[index] = new_string;
}

void	env_var_check(t_gen_data *data, char **env) // must free env paths
{
	int		count;
	int		i;
	int		j;
	char	**env_paths;

	count = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->quotes[i] == 1)
			parse_env_vars_quotes(data, env, data->executables[i], i);
		if (data->quotes[i] != 2)
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
		env_paths[j] = parse_env_vars(data, data->executables[i], env);
		free(data->executables[i]);
		data->executables[i] = env_paths[j];
		j++;
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
	env_var_check(data, env);
	set_pipe_flag(data);
}
