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

#include "../minishell.h"

void	pipe_children(t_gen_data *data, char **env, int i, int (*pipes)[2])
{
	char	**commands;

	signal(SIGINT, SIG_DFL);
	commands = pipe_divider(data->exec_copy, data->pipe_end);
	if (i > 0)
	{
		dup2(pipes[(i + 1) % 2][0], 0);
		close(pipes[(i + 1) % 2][0]);
		close(pipes[(i + 1) % 2][1]);
	}
	if (i < data->pipe_flag)
		dup2(pipes[i % 2][1], 1);
	close(pipes[i % 2][0]);
	close(pipes[i % 2][1]);
	if (data->executables)
		ft_free_tab(data->executables);
	data->executables = commands;
	exec_command(data, env);
	ft_free_tab(commands);
	exit(0);
}

void	pipe_parent(int (*pipes)[2], int i)
{
	if (i > 0)
	{
		close(pipes[(i + 1) % 2][0]);
		close(pipes[(i + 1) % 2][1]);
	}
}

void	pipe_setup(t_gen_data *data, int (*pipes)[2], int i)
{
	signal(SIGINT, SIG_IGN);
	if (pipe(pipes[i % 2]) == -1)
		ft_printf("pipe failure\n");
	data->pipe_end = pipe_index(data, data->exec_copy);
}

void	exec_pipe(t_gen_data *data, char **env)
{
	int		pipes[2][2];
	pid_t	pid1;
	int		i;

	data->exec_copy = executables_copy(data);
	i = 0;
	data->pipe_end = 0;
	while (i <= data->pipe_flag)
	{
		pipe_setup(data, pipes, i);
		pid1 = fork();
		if (pid1 < 0)
			ft_printf("fork failure\n");
		if (!pid1)
			pipe_children(data, env, i, pipes);
		else
			pipe_parent(pipes, i);
		i++;
	}
	while (wait(NULL) > 0)
		;
	signal(SIGINT, signal_handler);
}
