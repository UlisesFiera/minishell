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

#include "../minishell.h"

void	execve_handler(char *cmd_path, t_gen_data *data, char **env)
{
	signal(SIGINT, SIG_DFL);
	if (!cmd_path)
	{
		printf("couldn't find command: %s\n", data->executables[0]);
		free(cmd_path);
		exit(1);
	}
	if (execve(cmd_path, data->executables, env) == -1)
	{
		printf("couldn't execute command: %s\n", data->executables[0]);
		free(cmd_path);
		exit(1);
	}
}

void	exec_command(t_gen_data *data, char **env)
{
	char	*builts;
	char	*command;

	builts = "echo;cd;pwd;export;unset;env;exit";
	command = ft_strnstr(builts, data->executables[0], ft_strlen(builts));
	if (command && ft_strlen(command) > 2)
		exec_built(data, data->executables[0]);
	else
		exec_env(data, env);
}
