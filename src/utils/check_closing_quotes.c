/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closing_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:42:01 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/21 19:46:46 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_quote(char *input, int index)
{
	char	quote;

	quote = input[index];
	index++;
	while (input[index])
	{
		if (input[index] == quote)
			return (0);
		index++;
	}
	return (1);
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
