/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:37:48 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 11:42:30 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_path(char *env_var, char **env)
{
	char	*expanded_var;

	expanded_var = ft_getenv(env_var, env);
	if (!expanded_var)
	{
		expanded_var = malloc(1);
		expanded_var[0] = '\0';
		return (expanded_var);
	}
	return (ft_strdup(expanded_var));
}

char	*env_alloc(char *line, int index, t_gen_data *data)
{
	char	*var;
	int		start_i;
	int		i;

	start_i = index;
	while (line[index] && (line[index] == '_'
			|| (line[index] >= '0' && line[index] <= '9')
			|| (line[index] >= 'a' && line[index] <= 'z')
			|| (line[index] >= 'A' && line[index] <= 'Z')))
	{
		data->env_size++;
		index++;
	}
	var = malloc(data->env_size + 1);
	if (!var)
		fatal_error(data, "malloc");
	var[data->env_size] = '\0';
	i = 0;
	while (line[start_i] && (line[start_i] == '_'
			|| (line[start_i] >= '0' && line[start_i] <= '9')
			|| (line[start_i] >= 'a' && line[start_i] <= 'z')
			|| (line[start_i] >= 'A' && line[start_i] <= 'Z')))
		var[i++] = line[start_i++];
	return (var);
}

char	*expand_env(char *line, int i, t_gen_data *data, char **env)
{
	char	*var;
	char	*env_path;

	if (line[i] >= '0' && line[i] <= '9')
	{
		var = malloc(1);
		if (!var)
			fatal_error(data, "malloc");
		var[0] = '\0';
		data->env_size = 1;
		return (var);
	}
	var = env_alloc(line, i, data);
	env_path = get_env_path(var, env);
	if (!env_path)
	{
		var = malloc(1);
		if (!var)
			fatal_error(data, "malloc");
		var[0] = '\0';
		return (var);
	}
	free(var);
	return (env_path);
}

char	*exit_var(t_gen_data *data)
{
	char	*var;
	int		exit_status;

	if (WIFEXITED(data->prev_exit_status))
		exit_status = WEXITSTATUS(data->prev_exit_status);
	else
		exit_status = data->prev_exit_status;
	var = ft_itoa(exit_status);
	if (!var)
		fatal_error(data, "malloc");
	data->env_size = 1;
	return (var);
}

char	*env_var_str(char *line, int i, t_gen_data *data, char **env)
{
	data->env_size = 0;
	if (line[i] == '?')
		return (exit_var(data));
	else
		return (expand_env(line, i, data, env));
}
