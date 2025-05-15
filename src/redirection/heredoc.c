/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:31:20 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 17:31:20 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	collect_input(int *end, char *delimiter)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strcmp(line, delimiter))
	{
		write(end[1], line, ft_strlen(line));
		write(end[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
}

void	heredoc_parent(pid_t pid, int *end)
{
	close(end[0]);
	waitpid(pid, NULL, 0);
}

void	heredoc_child(int *end, char **commands, char **env, char *cmd_path)
{
	if (!cmd_path)
	{
		printf("couldn't find command: %s\n", commands[0]);
		free(cmd_path);
		exit(1);
	}
	dup2(end[0], 0);
	close(end[0]);
	if (execve(cmd_path, commands, env) == -1)
	{
		printf("couldn't find command: %s\n", commands[0]);
		free(cmd_path);
		exit(1);
	}
}

void	exec_heredoc(t_gen_data *data, char **env, int index)
{
	char	*cmd_path;
	char	*delimiter;
	char	**clean_commands_array;
	int		end[2];
	pid_t	pid;

	cmd_path = ft_get_path(data->executables[0], env);
	delimiter = data->executables[index + 1];
	clean_commands_array = array_cleaner(data);
	pipe(end);
	collect_input(end, delimiter);
	close(end[1]);
	pid = fork();
	if (!pid)
		heredoc_child(end, clean_commands_array, env, cmd_path);
	else if (pid > 0)
		heredoc_parent(pid, end);
    else
	{
		printf("Fork failed\n");
		free(cmd_path);
		ft_free_tab(clean_commands_array);
	}
	free(cmd_path);
	ft_free_tab(clean_commands_array);
}
