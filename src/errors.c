/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:32:58 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/21 18:05:09 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_error(t_gen_data *data, char *delimiter, int count)
{
	close(data->tmp_fds[count]);
	data->tmp_fds[count] = open(data->tmp_filenames[count], O_RDONLY, 0644);
	printf("-minishell: warning: here-document at line %i "
		"delimited by end-of-file (wanted %s)\n",
		data->lineno, delimiter);
}

void	syntax_error(char *token, t_gen_data *data)
{
	if (*token == '\n')
		printf("syntax error near unexpected token \"\\n\"\n");
	else
		printf("syntax error near unexpected token '%s'\n", token);
	data->exit_status = 2;
}

int	syntax_check(char *line, t_gen_data *data)
{
	if (line[0] == '|')
	{
		syntax_error(line, data);
		return (1);
	}
	return (0);
}
