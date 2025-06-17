/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:32:58 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/15 13:07:49 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    syntax_error(char *token, t_gen_data *data)
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