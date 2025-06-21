/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:36:53 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/21 19:36:53 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_loop(t_gen_data *data, char *cmd_path, int *heredoc_flag)
{
	int	i;
	int	count;

	count = 0;
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
		{
			*heredoc_flag = 1;
			count++;
		}
		i++;
	}
}

void	redirect_setter(t_gen_data *data, char *cmd_path, char **env)
{
	int	heredoc_flag;

	heredoc_flag = 0;
	signal(SIGINT, signal_handler_redir);
	redirect_loop(data, cmd_path, &heredoc_flag);
	if (heredoc_flag == 1)
	{
		generate_heredocs(data, env);
		exec_heredoc(data);
	}
}

void	child_redirect_handler(t_gen_data *data, char **clean_commands,
								char **env, char *cmd_path)
{
	redirect_setter(data, cmd_path, env);
	if (!env)
	{
		if (!ft_strcmp(clean_commands[0], "echo"))
			echo(clean_commands);
	}
	else
	{
		if (!clean_commands)
		{
			if (ft_strcmp(cmd_path, "unused"))
				free(cmd_path);
			exit(1);
		}
		if (execve(cmd_path, clean_commands, env) == -1)
		{
			printf("couldn't find command: %s\n",
				data->executables[data->executable_pos]);
			if (ft_strcmp(cmd_path, "unused"))
				free(cmd_path);
			exit(1);
		}
	}
}
