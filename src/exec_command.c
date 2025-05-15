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

	cmd_path = ft_get_path(data->executables[0], env);
	redir = redirect_check(data, env);
	if (!redir)
	{
		pid = fork();
		if (!pid)
			execve_handler(cmd_path, data, env);
		else if (pid > 0)
			wait(NULL);
		else
		{
			printf("Fork failed\n");
			free(cmd_path);
		}
	}
	free(cmd_path);
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
