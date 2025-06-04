/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:07:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/04 08:47:44 by ulfernan         ###   ########.fr       */
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
