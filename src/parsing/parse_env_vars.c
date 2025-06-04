/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:07:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/04 13:11:50 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*insert_env_var(t_gen_data *data, char *line, char **env, char **env_paths)
{
	int		i;
	int		j;
	int		skip;
	char	*new_string;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			env_paths[j] = env_cleaner(line + i + 1, env, data, line);
			skip = i;
			while (line[skip] && line[skip] != ' ')
				skip++;
			skip = skip - i;
			new_string = ft_strinsert(line, env_paths[j], i, skip);
			line = new_string;
			j++;
			i = 0;
		}
		else
			i++;
	}
	return (line);	
}

char	*parse_env_vars(t_gen_data *data, char *line, char **env)
{
	int		count;
	int		i;
	char	**env_paths;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count++;
		i++;
	}
	if (count == 0)
		return (line);
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	line = insert_env_var(data, line, env, env_paths);
	return (line);
}

char	*env_cleaner(char *executable, char **env, t_gen_data *data, char *full_exec) // must free
{
	char	*name;
	char	*path;
	char	*final_env;
	char	*sufix;
	int		i;
	int		size;
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
		path = malloc(1);
		path[1] = '\0';
		return (path);
	}
	if (executable[i] == '$')
	{
		size = 0;
		i++;
		index = i;
		while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') || (executable[i] >= 'a' && executable[i] <= 'z') || (executable[i] >= '0' && executable[i] <= '9')))
		{
			size++;
			i++;
		}
		sufix = malloc(size);
		sufix = env_cleaner(executable + index, env, data, full_exec);
		final_env = ft_strjoin(path, sufix);
		return (final_env);
	}
	return (path);
}

void	replace_env(t_gen_data *data, char **env_paths, char **env)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (data->executables[i])
	{
		if (data->quotes[i] != 2)
		{
			n = 0;
			while (data->executables[i][n])
			{
				if (data->executables[i][n] == '$')
				{
					env_paths[j] = parse_env_vars(data, data->executables[i], env);
					free(data->executables[i]);
					data->executables[i] = env_paths[j];
					j++;
				}
				n++;
			}
			i++;
		}
		else
			i++;
	}
}

void	parse_env_vars_quotes(t_gen_data *data, char **env, char *command, int index)
{
	char	*new_string;

	new_string = parse_env_vars(data, command, env);
	free(data->executables[index]);
	data->executables[index] = new_string;
}

void	env_var_count()
{
	int	count;
	int	i;
	int	j;

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
}

void	env_var_check(t_gen_data *data, char **env)
{
	int		count;
	int		i;
	int		j;
	char	**env_paths;

	count = env_var_count;
	if (count == 0)
		return ;
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	replace_env(data, env_paths, env);
}
