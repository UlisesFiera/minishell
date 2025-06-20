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

void	set_pipe_flag(t_gen_data *data)
{
	int	i;

	i = 0;
	while (data->executables[i])
	{
		if (!strcmp(data->executables[i], "|"))
		{
			if (i == 0)
			{
				syntax_error(data->executables[i], data);
				return ;
			}
			else
				data->pipe_flag++;
		}
		i++;
	}
}

int	pipe_index(t_gen_data *data, char **commands)
{
	if (!commands[data->pipe_index])
		return (data->pipe_index);
	if (commands[data->pipe_index][0] == '|')
		data->pipe_index++;
	while (commands[data->pipe_index])
	{
		if (commands[data->pipe_index][0] == '|')
			return (data->pipe_index);
		data->pipe_index++;
	}
	return (data->pipe_index);
}

char	**executables_copy(t_gen_data *data)
{
	char	**copy;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (data->executables[i])
	{
		size++;
		i++;
	}
	copy = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (data->executables[i])
	{
		copy[i] = ft_strdup(data->executables[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	exec_pipe(t_gen_data *data, char **env)
{
	int		pipes[2][2];
	pid_t	pid1;
	char	**commands;
	int		index;
	int		i;

	data->exec_copy = executables_copy(data);
	i = 0;
	index = 0;
	while (i <= data->pipe_flag)
	{
		if (pipe(pipes[i % 2]) == -1)
			ft_printf("pipe failure\n");
		index = pipe_index(data, data->exec_copy);
		signal(SIGINT, SIG_IGN);
		pid1 = fork();
		if (pid1 < 0)
			ft_printf("fork failure\n");
		if (!pid1)
		{
			signal(SIGINT, SIG_DFL);
			commands = pipe_divider(data->exec_copy, index);
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
			data->executables = commands;
			exec_command(data, env);
			exit(0);
		}
		else
		{
			if (i > 0)
			{
				close(pipes[(i + 1) % 2][0]);
				close(pipes[(i + 1) % 2][1]);
			}
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	signal(SIGINT, signal_handler);
}
