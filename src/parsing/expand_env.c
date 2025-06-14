/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:26:00 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/04 13:26:00 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_digit_start(char *executable)
{
	int		i;
	int		index;
	char	*final_env;

	i = 0;
	if (executable[i] >= '0' && executable[i] <= '9')
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
	final_env[i] = '\0';
	return (final_env);
}

char	*expand_exit(t_gen_data *data)
{
	char	*final_env;
	int		exit_status;

	exit_status = WEXITSTATUS(data->last_exit_status);
	final_env = ft_itoa(exit_status);
	return (final_env);
}

char	*expand_env(char *executable, char **env, t_gen_data *data) // must free
{
	char	*env_var;
	char	*final_env;

	if (*executable == '?')
		return (final_env = expand_exit(data));
	if (executable[0] >= '0' && executable[0] <= '9')
		return (final_env = expand_digit_start(executable));
	env_var = get_env_var(executable, env, data);
	return (env_var);
}