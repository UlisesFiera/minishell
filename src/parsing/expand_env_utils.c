/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:37:39 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/04 13:37:39 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*concatenated_env_vars(t_gen_data *data, char **env, char *executable, 
								int i, char *expanded_var)
{
	int		size;
	int		index;
	char	*sufix;
	char	*final_var;

	size = 0;
	i++;
	index = i;
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') 
		|| (executable[i] >= 'a' && executable[i] <= 'z') 
		|| (executable[i] >= '0' && executable[i] <= '9')))
	{
		size++;
		i++;
	}
	sufix = malloc(size);
	sufix = expand_env(executable + index, env, data);
	final_var = ft_strjoin(expanded_var, sufix);
	return (final_var);
}

char	*get_env_path(char *env_var, char **env)
{
	char	*expanded_var;

	expanded_var = ft_getenv(env_var, env);
	if (!expanded_var)
	{
		expanded_var = malloc(1);
		expanded_var[1] = '\0';
		return (expanded_var);
	}
	return (expanded_var);
}

char	*get_env_var(char *executable, char **env, t_gen_data *data)
{
	int		i;
	char	*env_var;
	char	*expanded_var;

	i = 0;
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') 
		|| (executable[i] >= 'a' && executable[i] <= 'z') 
		|| (executable[i] >= '0' && executable[i] <= '9')))
	i++;
	env_var = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z') 
		|| (executable[i] >= 'a' && executable[i] <= 'z') 
		|| (executable[i] >= '0' && executable[i] <= '9')))
	{
		env_var[i] = executable[i];
		i++;
	}
	env_var[i] = '\0';
	expanded_var = get_env_path(env_var, env);
	if (executable[i] == '$')
	{
		expanded_var = concatenated_env_vars(data, env, executable, i, expanded_var);
		return (expanded_var);
	}
	return (expanded_var);
}
