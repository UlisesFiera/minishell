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
		printf("couldn't find command: %s\n", data->executables[0]);
		free(cmd_path);
		exit(1);
	}
}

void	exec_env(t_gen_data *data, char **env)
{
	char	*cmd_path;
	int		redir;
	pid_t	pid;

	if (data->executables[0][0] == '/' || data->executables[0][1] == '/')
		cmd_path = ft_strdup(data->executables[0]);
	else	
		cmd_path = ft_get_path(data->executables[0], env);
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
	free(cmd_path);
}

void	execbuilt_handler(t_gen_data *data, char *command)
{
	if (!ft_strcmp(command, "echo"))
		echo(data, data->executables);
}

void	exec_builts(t_gen_data *data, char *command)
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

void	exec_command(t_gen_data *data, char **env)
{
	char	*builts;
	char	*command;

	builts = "echo;cd;pwd;export;unset;env;exit";
	command = ft_strnstr(builts, data->executables[0], ft_strlen(builts));
	if (command)
		exec_builts(data, data->executables[0]);
	else
		exec_env(data, env);
}
