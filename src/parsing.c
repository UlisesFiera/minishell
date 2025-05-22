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

char	*env_cleaner(char *executable, char **env) // must free
{
	char	*name;
	char	*path;
	char	*sufix;
	char	*final_env;
	int		i;
	int		j;
	int		index;

	i = 0;
	while (executable[i] && executable[i] >= 'A' && executable[i] <= 'Z')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (executable[i] && executable[i] >= 'A' && executable[i] <= 'Z')
	{
		name[i] = executable[i];
		i++;
	}
	name[i] = '\0';
	path = ft_getenv(name, env);
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
	sufix[i] = '\n';
	final_env = ft_strjoin(path, sufix);
	return (final_env);
}

void	parse_env_vars(t_gen_data *data, char **env) // must free env paths
{
	int		count;
	int		i;
	char	**env_paths;

	count = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->executables[i][0] == '$')
			count++;
		i++;
	}
	env_paths = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (data->executables[i])
	{
		if (data->executables[i][0] == '$')
		{
			env_paths[i] = env_cleaner(data->executables[i] + 1, env);
			free(data->executables[i]);
			data->executables[i] = env_paths[i];
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
	index = 0;
	i = 0;
	while(i < exec_count)
	{
		data->executables[i] = exec_split(data->input, &index);
		i++;
	}
	parse_env_vars(data, env);
	set_pipe_flag(data);
}
