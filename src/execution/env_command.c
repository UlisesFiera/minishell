/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:48:24 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/20 18:48:24 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_env_fork(t_gen_data *data, char **env, char *cmd_path)
{
	int		redir;
	pid_t	pid;

	redir = redirect(data, env);
	if (!redir)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (!pid)
			execve_handler(cmd_path, data, env);
		else if (pid > 0)
		{
			wait(&data->exit_status);
			signal(SIGINT, signal_handler);
		}
		else
		{
			printf("Fork failed\n");
			free(cmd_path);
		}
	}
	if (cmd_path)
		free(cmd_path);
}

void	exec_env(t_gen_data *data, char **env)
{
	char	*cmd_path;

	if (data->executables[0][0] == '/' || data->executables[0][1] == '/')
		cmd_path = ft_strdup(data->executables[0]);
	else
		cmd_path = ft_get_path(data->executables[0], env);
	exec_env_fork(data, env, cmd_path);
}
