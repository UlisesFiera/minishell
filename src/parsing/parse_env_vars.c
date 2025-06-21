/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:07:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/21 17:17:55 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_count(char *line, int i)
{
	int	skip;

	skip = i;
	while (line[skip] && line[skip] != ' '
		&& line[skip] != '\'' && line[skip] != '"')
		skip++;
	skip = skip - i;
	return (skip);
}

char	*insert_env_var(
			t_gen_data *data, char *line, char **env, char **env_paths)
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
			env_paths[j] = expand_env(line + i + 1, env, data);
			skip = skip_count(line, i);
			new_string = ft_strinsert(line, env_paths[j], i, skip);
			free(line);
			line = new_string;
			j++;
			i = 0;
			free(env_paths[i]);
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
	free(env_paths);
	return (line);
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
					env_paths[j] = parse_env_vars(
							data, data->executables[i], env);
					data->executables[i] = env_paths[j++];
				}
				n++;
			}
		}
		i++;
	}
}

void	parse_env_vars_quotes(
			t_gen_data *data, char **env, char *command, int index)
{
	char	*new_string;

	new_string = parse_env_vars(data, command, env);
	free(data->executables[index]);
	data->executables[index] = new_string;
}
