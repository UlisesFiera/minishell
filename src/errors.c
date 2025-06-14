/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:32:58 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/13 11:10:00 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    syntax_error(char *token, t_gen_data *data)
{
    printf("syntax error near unexpected token '%s'\n", token);
    data->exit_status = 2;
}

int	syntax_check(char *line, t_gen_data *data)
{
	if (line[0] == '|' || line[0] == '<' || line[0] == '>')
	{
		syntax_error(line, data);
		return (1);
	}
	return (0);
}