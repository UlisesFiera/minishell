/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:07:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/14 15:41:28 by ulfernan         ###   ########.fr       */
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
			env_paths[j] = expand_env(line + i + 1, env, data);
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
		}
		i++;
	}
}

void	parse_env_vars_quotes(t_gen_data *data, char **env, char *command, int index)
{
	char	*new_string;
	char	*last_q;
	char	*final_string;
	int		i;

	new_string = ft_strdup(parse_env_vars(data, command, env));
	i = 1;
	while (command[i] != '\0' && command[i] != '\'')
		i++;
	if (command[i] == '\'')
	{
		last_q = &data->executables[index][i];
		final_string = ft_strjoin(new_string, last_q);
		free(data->executables[index]);
		data->executables[index] = final_string;
	}
	else
	{
		free(data->executables[index]);
		data->executables[index] = new_string;
	}
}
