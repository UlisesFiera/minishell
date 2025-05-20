/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_executables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:39:09 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/20 08:47:16 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_quote(char *input, int index) // we check if the quote is grouping a command or if it's single
{
	while (input[index])
	{
		if (input[index] == '"' || input[index] == '\'')
			return (0);
		index++;
	}
	return (1);
}

int	exec_size(char *input, int i, int *quotes)
{
	int	size;

	size = 0;
	while (input[i] == ' ')
		i++;
	while (input[i] != '\0' && input[i] != ' ' && !*quotes)
	{
		if ((input[i] == '"' || input[i] == '\'') && !find_quote(input, i + 1))
		{
			*quotes = 1;
			while (input[++i] != '\0' && input[i] != '"' && input[i] != '\'')
				size++;
			if (input[i] == '"' || input[i] == '\'')
				i++;
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

static void	fill_exec(char *executable, char *input, int *index, int quotes)
{
	int	i;
	
	i = 0;
	while (input[*index] == ' ')
		(*index)++;
	if (quotes)
	{
		(*index)++;
		while (input[*index] && input[*index] != '"' && input[*index] != '\'')
			executable[i++] = input[(*index)++];
		if (input[*index] == '"' || input[*index] == '\'')
			(*index)++;
	}
	else
	{
		while (input[*index] != '\0' && input[*index] != ' ')
			executable[i++] = input[(*index)++];
	}
	executable[i] = '\0';
}

char	*exec_split(char *input, int *index)
{
	char	*executable;
	int		quotes;
	int		i;
	int		size;

	i = *index;
	quotes = 0;
	size = exec_size(input, i, &quotes);
	executable = malloc(sizeof(char) * size + 1);
	if (!executable)
		return (NULL);
	fill_exec(executable, input, index, quotes);
	return (executable);
}
