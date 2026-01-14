/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:13:11 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 11:13:11 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_env_command_parent(t_gen_data *data)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_signal_status = 1;
	wait(&data->last_exit_status);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (WIFSIGNALED(data->last_exit_status))
	{
		if (WTERMSIG(data->last_exit_status) == SIGINT)
			write(1, "\n", 1);
		data->last_exit_status = WTERMSIG(data->last_exit_status) + 128;
	}
}

int	execute_env_command(t_command *command, t_gen_data *data, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		fatal_error(data, "fork");
	else if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		data->last_exit_status = redirect_setup(command, data);
		{
			if (data->last_exit_status != 0)
				exit(data->last_exit_status);
		}
		data->last_exit_status = execve_handler(command, env);
		exit(data->last_exit_status);
	}
	else
		execute_env_command_parent(data);
	return (data->last_exit_status);
}
