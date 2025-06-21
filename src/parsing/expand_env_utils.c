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
								char *expanded_var)
{
	int		size;
	int		index;
	char	*sufix;
	char	*final_var;
	int		i;

	size = 0;
	i = data->env_var_index;
	i++;
	index = i;
	while (executable[i] && ((executable[i] >= 'A' && executable[i] <= 'Z')
			|| (executable[i] >= 'a' && executable[i] <= 'z')
			|| (executable[i] >= '0' && executable[i] <= '9')))
	{
		size++;
		i++;
	}
	sufix = expand_env(executable + index, env, data);
	final_var = ft_strjoin(expanded_var, sufix);
	if (expanded_var)
		free(expanded_var);
	if (sufix)
		free(sufix);
	return (final_var);
}

char	*get_env_path(char *env_var, char **env)
{
	char	*expanded_var;

	expanded_var = ft_getenv(env_var, env);
	if (!expanded_var)
	{
		expanded_var = malloc(2);
		expanded_var[0] = ' ';
		expanded_var[1] = '\0';
		return (expanded_var);
	}
	return (ft_strdup(expanded_var));
}

char	*expand_env_var(t_gen_data *data, char **env, char *executable)
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
	free(env_var);
	data->env_var_index = i;
	return (expanded_var);
}

char	*get_env_var(char *executable, char **env, t_gen_data *data)
{
	char	*expanded_var;

	expanded_var = expand_env_var(data, env, executable);
	if (executable[data->env_var_index] == '$')
	{
		expanded_var = concatenated_env_vars(
				data, env, executable, expanded_var);
		return (expanded_var);
	}
	return (expanded_var);
}
