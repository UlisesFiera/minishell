/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closing_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:42:01 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 16:29:43 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_closing_quote(t_gen_data *data, int index)
{
	char	quote;

	if (data->input[index])
	{
		quote = data->input[index];
		index++;
		while (data->input[index])
		{
			if (data->input[index] == quote)
				return (index);
			index++;
		}
	}
	data->exec_count = -1;
	data->exit_loop = 1;
	return (-1);
}

int	odd_quotes(char *input, int index)
{
	char	quote;
	int		count;
	int		i;

	quote = input[index];
	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == quote)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}
