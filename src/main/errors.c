/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:32:58 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:34 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_error(t_command *command, char **cmd_path, int errcode)
{
	if (errcode == 0)
	{
		ft_putstr_fd("couldn't find command: ", 2);
		ft_putendl_fd(command->argv[0], 2);
		free(*cmd_path);
		return (127);
	}
	else
	{
		ft_putstr_fd("command found but not executable: ", 2);
		ft_putendl_fd(command->argv[0], 2);
		free(*cmd_path);
		return (126);
	}
}

void	heredoc_error(t_gen_data *data, char *delimiter)
{
	ft_putstr_fd("\n-minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(data->lineno, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted ", 2);
	ft_putstr_fd(delimiter, 2);
	write(2, ")\n", 2);
}

void	syntax_error(char *token, t_gen_data *data, int optcode)
{
	if (optcode == 0)
		ft_putendl_fd(
			"minishell: syntax error near unexpected token \"\\n\"", 2);
	else if (optcode == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putendl_fd(token, 2);
	}
	else if (optcode == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token, 2);
		ft_putendl_fd(" ambiguous redirect", 2);
	}
	else if (optcode == 3)
	{
		ft_putstr_fd("minishell: parse error near ", 2);
		ft_putendl_fd(token, 2);
	}
	data->exit_loop = 1;
	data->last_exit_status = 258;
}

void	unclosed_token_error(char *token, t_gen_data *data)
{
	if (*token == '|' || *token == '"' || *token == '\'')
	{
		ft_putstr_fd("minishell: error: unclosed redirector found: ", 2);
		ft_putendl_fd(token, 2);
		data->exit_loop = 1;
		data->last_exit_status = 255;
	}
}

void	fatal_error(t_gen_data *data, char *error_code)
{
	if (!ft_strcmp(error_code, "malloc"))
		ft_putendl_fd("minishell: malloc failure: couldn't allocate memory", 2);
	if (!ft_strcmp(error_code, "env"))
		ft_putendl_fd("minishell: fatal: environment variables not set.", 2);
	if (!ft_strcmp(error_code, "count"))
		ft_putendl_fd("minishell: error counting args", 2);
	if (!ft_strcmp(error_code, "count"))
		ft_putendl_fd("minishell: pipe allocation error", 2);
	if (!ft_strcmp(error_code, "fork"))
		ft_putendl_fd("minishell: error while forking", 2);
	if (!ft_strcmp(error_code, "fd"))
		ft_putendl_fd("heredoc: couldn't open heredoc file", 2);
	free_data(data);
	exit(1);
}
