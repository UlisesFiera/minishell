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

void	pipe_child(int *end, t_gen_data *data, char **env, char **commands_left)
{
	data->executables = commands_left;
	dup2(end[1], 1);
	close(end[0]); // Close unused read end in child
	close(end[1]); // Close write end after dup2
	exec_command(data, env);
	exit(1);
}

void	pipe_parent(int *end, t_gen_data *data, char **env, char **commands_right) // we need to fork again because otherwise we'd terminate the shell after using execve in the parent
{
	pid_t	pid2;

	data->executables = commands_right;
	wait(NULL); // Wait for first child
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(end[0], 0);
		close(end[1]); // Close unused write end in right child
		close(end[0]); // Close read end after dup2
		exec_command(data, env);
		exit(1);
	}
	else
	{
		close(end[0]); // Close both ends in parent
		close(end[1]);
		wait(NULL);
	}
}

void	exec_pipe(t_gen_data *data, char **env)
{
	int		end[2];
	pid_t	pid1;
	char	**commands_left;
	char	**commands_right;

	commands_left = pipe_divider(data, 0);
	commands_right = pipe_divider(data, 1);
	ft_free_tab(data->executables);
	if (pipe(end) == -1)
		ft_printf("pipe failure\n");
	pid1 = fork();
	if (pid1 < 0)
		ft_printf("fork failure\n");
	if (!pid1)
		pipe_child(end, data, env, commands_left);
	else
		pipe_parent(end, data, env, commands_right);
}
