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

void	child_redirect_handler(t_gen_data *data, char **clean_commands, 
								char **env, char *cmd_path)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	signal(SIGINT, SIG_DFL);
	while (data->executables[i])
	{
		if (!ft_strcmp(data->executables[i], "<"))
			exec_from_input(data, i, cmd_path);
		else if (!ft_strcmp(data->executables[i], ">"))
			exec_to_output(data, i, cmd_path);
		else if (!ft_strcmp(data->executables[i], ">>"))
			exec_append(data, i, cmd_path);
		else if (!ft_strcmp(data->executables[i], "<<"))
		{
			exec_heredoc(data, i, count);
			count++;
		}
		i++;
	}
	if (!env)
	{
		if (!ft_strcmp(clean_commands[0], "echo"))
			echo(data, clean_commands);
	}
	else
	{
		if (execve(cmd_path, clean_commands, env) == -1)
		{
			printf("couldn't find command: %s\n", data->executables[0]);
			free(cmd_path);
			exit(1);
		}
	}
}

void	redirect_handler(t_gen_data *data, char **clean_commands, char **env)
{
	char	*cmd_path;
	pid_t	pid;

	if (env)
		cmd_path = ft_get_path(data->executables[0], env);
	else
		cmd_path = "unused";
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		child_redirect_handler(data, clean_commands, env, cmd_path);
	else if (pid > 0)
	{
		wait(&data->exit_status);
		signal(SIGINT, signal_handler);
		if (ft_strcmp(cmd_path, "unused"))
			free(cmd_path);
	}
    else
	{
		printf("Fork failed\n");
		if (ft_strcmp(cmd_path, "unused"))
			free(cmd_path);
    }
}

int	redirect(t_gen_data *data, char **env)
{
	char	**clean_commands;
	int		i;

	i = 0;
	while (data->executables[i])
	{
		if (!ft_strcmp(data->executables[i], "<") ||
				!ft_strcmp(data->executables[i], "<<") ||
				!ft_strcmp(data->executables[i], ">") ||
				!ft_strcmp(data->executables[i], ">>"))
		{
			clean_commands = array_cleaner_left(data);
			redirect_handler(data, clean_commands, env);
			free(clean_commands);
			return (1);
		}
		i++;
	}
	return (0);
}
