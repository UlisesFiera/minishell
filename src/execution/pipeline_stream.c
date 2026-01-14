/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_stream.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:25:27 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/31 01:23:58 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_parent(t_gen_data *data, pid_t *pid)
{
	int	i;

	i = 0;
	g_signal_status = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < data->pipe_count * 2)
		close(data->pipe_ends[i++]);
	i = 0;
	while (i <= data->pipe_count)
		waitpid(pid[i++], &data->last_exit_status, 0);
	if (WIFSIGNALED(data->last_exit_status))
	{
		data->last_exit_status = 128 + WTERMSIG(data->last_exit_status);
		write(1, "\n", 1);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	manage_fds(t_gen_data *data, int index)
{
	int	i;

	if (index == 0)
		dup2(data->pipe_ends[1], 1);
	else if (index == data->pipe_count)
		dup2(data->pipe_ends[data->pipe_count * 2 - 2], 0);
	else
	{
		dup2(data->pipe_ends[(index - 1) * 2], 0);
		dup2(data->pipe_ends[index * 2 + 1], 1);
	}
	i = 0;
	while (i < data->pipe_count * 2)
		close(data->pipe_ends[i++]);
}

void	fork_commands(
	t_command **commands, t_gen_data *data, char **env, pid_t *pid)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		pid[i] = fork();
		if (pid[i] < 0)
			fatal_error(data, "fork");
		else if (!pid[i])
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			manage_fds(data, i);
			data->last_exit_status = redirect_setup(commands[i], data);
			{
				if (data->last_exit_status != 0)
					exit(data->last_exit_status);
			}
			data->last_exit_status = execute_command(commands[i], data, env);
			exit(data->last_exit_status);
		}
		i++;
	}
	main_parent(data, pid);
}

void	pipeline_stream(t_command **commands, t_gen_data *data, char **env)
{
	pid_t	*pid;
	int		i;

	data->pipe_ends = malloc(sizeof(int) * (data->pipe_count * 2));
	if (!data->pipe_ends)
		fatal_error(data, "malloc");
	i = 0;
	while (i < data->pipe_count)
	{
		if (pipe(&data->pipe_ends[i * 2]) == -1)
			fatal_error(data, "pipe");
		i++;
	}
	pid = NULL;
	pid = malloc(sizeof(pid_t) * (data->pipe_count + 1));
	if (!pid)
		fatal_error(data, "malloc");
	fork_commands(commands, data, env, pid);
	if (pid)
		free(pid);
	if (data->pipe_ends != NULL)
		free(data->pipe_ends);
	data->pipe_ends = NULL;
}
