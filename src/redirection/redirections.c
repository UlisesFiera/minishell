/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:56:49 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 16:56:49 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_handler(t_gen_data *data, char **clean_commands, char **env)
{
	int		i;
	char	*cmd_path;
	pid_t	pid;

	cmd_path = ft_get_path(data->executables[0], env);
	pid = fork();
	if (!pid)
	{
		i = 0;
		while (data->executables[i])
		{
			if (!ft_strcmp(data->executables[i], "<"))
				exec_from_input(data, i, cmd_path);
			else if (!ft_strcmp(data->executables[i], ">"))
				exec_to_output(data, i, cmd_path);
			else if (!ft_strcmp(data->executables[i], ">>"))
				exec_append(data, i, cmd_path);
			else if (!ft_strcmp(data->executables[i], "<<")) 
				exec_heredoc(data, i, cmd_path);
			i++;
		}
		if (data->input_fd != -1)
			dup2(data->input_fd, 0);
		if (execve(cmd_path, clean_commands, env) == -1)
		{
			printf("couldn't find command: %s\n", data->executables[0]);
			free(cmd_path);
			exit(1);
		}
	}
	else if (pid > 0)
	{
		wait(NULL);
		free(cmd_path);
	}
    else
	{
		printf("Fork failed\n");
		free(cmd_path);
    }
}

int	redirect(t_gen_data *data, char **env)
{
	char	**clean_commands;
	char	*symbol;
	int		i;

	symbol = "<;<<;>;>>";
	i = 0;
	while (data->executables[i])
	{
		if (ft_strnstr(symbol, data->executables[i], ft_strlen(symbol)))
		{
			//if (data->pipe_flag) in case of pipe we split the commands <- | -> and pipe them
			clean_commands = array_cleaner_left(data);
			redirect_handler(data, clean_commands, env);
			free(clean_commands);
			return (1);
		}
		i++;
	}
	return (0);
}
