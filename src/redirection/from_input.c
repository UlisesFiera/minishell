/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:31:51 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 17:31:51 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(char *file, char **commands, char **env, char *cmd_path, t_gen_data *data)
{
	int	stdin;
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	stdin = dup(0);
	dup2(fd, 0);
	close(fd);
	if (execve(cmd_path, commands, env) == -1)
	{
		printf("couldn't find command: %s\n", commands[0]);
		dup2(stdin, 0);
		close(stdin);
		free(cmd_path);
		data->input = NULL;
		exit(1);
	}
}

void	exec_from_input(t_gen_data *data, char **env, int index)
{
	char	*cmd_path;
	char	*file;
	char	**clean_commands_array;
	pid_t	pid;

	cmd_path = ft_get_path(data->executables[0], env);
	file = data->executables[index + 1];
	clean_commands_array = array_cleaner(data);
	pid = fork();
	if (!pid)
		child(file, clean_commands_array, env, cmd_path, data);
	else if (pid > 0)
	{
		wait(NULL);
		free(cmd_path);
	}
    else
	{
		printf("Fork failed\n");
		free(cmd_path);
		data->input = NULL;
    }
}
