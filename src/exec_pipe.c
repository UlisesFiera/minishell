/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:55:37 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/16 16:55:37 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **commands, char **env)
{
	char	*cmd_path;

	cmd_path = ft_get_path(commands[0], env);
	if (!cmd_path)
	{
		printf("couldn't find command: %s\n", commands[0]);
		free(cmd_path);
		exit(1);
	}
	if (execve(cmd_path, commands, env) == -1)
	{
		ft_printf("execve couldn't find command: %s\n", commands[0]);
		free(cmd_path);
		exit(0);
	}
}

void	child(int *end, t_gen_data *data, char **env)
{
	char	**array_left;

	array_left = array_cleaner_left(data);
	dup2(end[1], 1);
	close(end[0]);
	execute(array_left, env);
}

void	parent(int *end, t_gen_data *data, char **env)
{
	char	**array_right;

	array_right = array_cleaner_right(data, 0);
	wait(NULL);
	dup2(end[0], 0);
	close(end[1]);
	execute(array_right, env);
}

void	exec_pipe(t_gen_data *data, char **env)
{
	int		end[2];
	pid_t	pid1;

	if (pipe(end) == -1)
		ft_printf("pipe failure\n");
	pid1 = fork();
	if (pid1 < 0)
		ft_printf("fork failure\n");
	if (!pid1)
		child(end, data, env);
	else
		parent(end, data, env);
}