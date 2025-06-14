/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:56:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/14 16:43:23 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_single_quote(char *input, int *i)
{
	if (!find_quote(input, *i))
	{
		while (input[*i] != '\0' && input[*i] != '\'')
			(*i)++;
	}
}

void	skip_double_quote(char *input, int *i)
{
	if (!find_quote(input, *i))
	{
		while (input[*i] != '\0' && input[*i] != '"')
			(*i)++;
	}
}

int	exec_counter(char *input)
{
	int		exec_count;
	int		q_flag;
	int		i;

	exec_count = 0;
	i = 0;
	while (input[i])
	{
		q_flag = 0;
		while (input[i] == ' ')
			i++;
		if (input[i] != '\0')
			exec_count++;
		if (input[i] == '\'' || input[i] == '"')
		{
			if (input[i] == '"')
				skip_double_quote(input, &i);
			else if (input[i] == '\'')
				skip_single_quote(input, &i);
			q_flag = 1;
			i++;
		}
		while (input[i] != '\0' && input[i] != ' ' && !q_flag)
			i++;
	}
	return (exec_count);
}
