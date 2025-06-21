/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:48:34 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/20 18:48:34 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execbuilt_handler(t_gen_data *data, char *command)
{
	if (!ft_strcmp(command, "echo"))
		echo(data->executables);
}

void	exec_built(t_gen_data *data, char *command)
{
	pid_t	pid;
	int		redir;

	redir = redirect(data, NULL);
	if (!redir)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (!pid)
			execbuilt_handler(data, command);
		else if (pid > 0)
		{
			wait(&data->exit_status);
			signal(SIGINT, signal_handler);
		}
		else
			printf("Fork failed\n");
	}
}
