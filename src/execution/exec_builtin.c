/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:12:37 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 11:12:37 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin_child(
		char *builtin, t_command *command, t_gen_data *data, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	data->last_exit_status = redirect_setup(command, data);
	{
		if (data->last_exit_status != 0)
			exit(data->last_exit_status);
	}
	data->last_exit_status = builtin_handler(
			builtin, command, data, env);
	exit(data->last_exit_status);
}

int	execute_builtin(
		char *builtin, t_command *command, t_gen_data *data, char **env)
{
	pid_t	pid;

	if (data->redir_count > 0
		&& ft_strcmp(builtin, "cd") && ft_strcmp(builtin, "exit")
		&& ft_strcmp(builtin, "export") && ft_strcmp(builtin, "unset"))
	{
		pid = fork();
		if (pid < 0)
			fatal_error(data, "fork");
		else if (!pid)
			execute_builtin_child(builtin, command, data, env);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			wait(&data->last_exit_status);
			signal(SIGINT, signal_handler);
			signal(SIGQUIT, SIG_IGN);
		}
		return (data->last_exit_status);
	}
	data->last_exit_status = builtin_handler(builtin, command, data, env);
	return (data->last_exit_status);
}
