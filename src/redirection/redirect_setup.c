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

int	redir_first(t_gen_data *data)
{
	if (!data->executables[1])
	{
		syntax_error("\n", data);
		return (-1);
	}
	return (2);
}

int	find_executable(t_gen_data *data)
{
	int	i;

	if (!ft_strcmp(data->executables[0], "<")
		|| !ft_strcmp(data->executables[0], "<<")
		|| !ft_strcmp(data->executables[0], ">")
		|| !ft_strcmp(data->executables[0], ">>"))
		return (redir_first(data));
	i = 0;
	while (data->executables[i])
		i++;
	if (!ft_strcmp(data->executables[i - 1], "<")
		|| !ft_strcmp(data->executables[i - 1], "<<")
		|| !ft_strcmp(data->executables[i - 1], ">")
		|| !ft_strcmp(data->executables[i - 1], ">>"))
	{
		syntax_error("\n", data);
		return (-1);
	}
	return (0);
}

void	redirect_fork(t_gen_data *data,
			char **clean_commands, char **env, char *cmd_path)
{
	pid_t	pid;

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

void	redirect_handler(t_gen_data *data, char **clean_commands, char **env)
{
	char	*cmd_path;

	if (env)
	{
		if (data->executables[data->executable_pos])
			cmd_path = ft_get_path(
					data->executables[data->executable_pos], env);
		else
			cmd_path = "unused";
	}
	else
		cmd_path = "unused";
	signal(SIGINT, SIG_IGN);
	redirect_fork(data, clean_commands, env, cmd_path);
}

int	redirect(t_gen_data *data, char **env)
{
	char	**clean_commands;
	int		i;

	i = 0;
	while (data->executables[i])
	{
		if (!ft_strcmp(data->executables[i], "<")
			|| !ft_strcmp(data->executables[i], "<<")
			|| !ft_strcmp(data->executables[i], ">")
			|| !ft_strcmp(data->executables[i], ">>"))
		{
			data->executable_pos = find_executable(data);
			if (data->executable_pos < 0)
				return (1);
			clean_commands = array_cleaner_left(data);
			redirect_handler(data, clean_commands, env);
			free(clean_commands);
			return (1);
		}
		i++;
	}
	return (0);
}
