/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:35:06 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/12 13:35:06 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_gen_data *data, char **env)
{
	(void)data;
	(void)env;
}

void	exec_mini_env(t_gen_data *data)
{
	(void)data;
}

void	exec_command(t_gen_data *data, char **env)
{
	char	*mini_env;
	char	*command;

	mini_env = "echo;cd;pwd;export;unset;env;exit";
	command = ft_strnstr(mini_env, data->executables[0], ft_strlen(mini_env));
	if (command)
		exec_mini_env(data);
	else
		exec_env(data, env);
}