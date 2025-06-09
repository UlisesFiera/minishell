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

char	**parse_prompt_for_pipes(char *line)
{
	char	**new_commands;
	int		exec_count;
	int		index;
	int		i;

	exec_count = exec_counter(line);
	new_commands = malloc(sizeof(char *) * (exec_count + 1));
	if (!new_commands)
		return (NULL);
	new_commands[exec_count] = NULL;
	index = 0;
	i = 0;
	while (i < exec_count)
	{
		new_commands[i] = exec_split(line, &index, i, NULL);
		i++;
	}
	return (new_commands);
}

void	copy_all_commands(char **commands, char **new_commands, char **all_commands)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (commands[i])
		all_commands[j++] = commands[i++];
	i = 0;
	while (new_commands[i])
		all_commands[j++] = new_commands[i++];
	all_commands[j] = NULL;
}

char *readline_in_pipe(char *prompt) // we save the pipe's stdout so we can momentarily swap it for the terminal's fd so we can see our prompt
{
	int		tty_fd;
	int		saved_stdout;
	char	*line;

	tty_fd = open("/dev/tty", O_WRONLY);
	if (tty_fd == -1)
		return (NULL);
	saved_stdout = dup(1);
	dup2(tty_fd, 1);
	close(tty_fd);
	line = readline(prompt);
	dup2(saved_stdout, 1);
	close(saved_stdout);
	return (line);
}

char	**prompt_for_pipes(char **commands)
{
	char	*line;
	char	**new_commands;
	char	**all_commands;
	int		count;
	int		i;

	line = readline_in_pipe("> ");
	while (line[0] == '\n')
	{
		new_commands = parse_prompt_for_pipes(line);
		free(line);
		line = readline_in_pipe("> ");
	}
	count = 0;
	while (new_commands[count])
		count++;
	i = 0;
	while (commands[i])
		count++;
	all_commands = malloc(sizeof (char *) * count + 1);
	copy_all_commands(commands, new_commands, all_commands);
	return (all_commands);
}

void	exec_pipe(t_gen_data *data, char **env)
{
	int		pipes[2][2];
	pid_t	pid1;
	char	**exec_copy;
	char	**commands;
	int		index;
	int		i;

	printf("%d\n", data->pipe_flag);
	exec_copy = executables_copy(data);
	i = 0;
	index = 0;
	while (i <= data->pipe_flag)
	{
		if (pipe(pipes[i % 2]) == -1)
			ft_printf("pipe failure\n");
		index = pipe_index(data, exec_copy);
		signal(SIGINT, SIG_IGN);
		pid1 = fork();
		if (pid1 < 0)
			ft_printf("fork failure\n");
		if (!pid1)
		{
			signal(SIGINT, SIG_DFL);
			commands = pipe_divider(exec_copy, index);
			if (!exec_copy[index + 1])
				commands = prompt_for_pipes(commands);

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
