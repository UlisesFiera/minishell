/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_executables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:39:09 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/09 12:20:52 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_quote(char *input, int index) // we check if the quote is grouping a command or if it's single
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

int	exec_size(char *input, int i, char *quotes)
{
	int	size;

	size = 0;
	while (input[i] == ' ')
		i++;
	while (input[i] != '\0' && (*quotes != '\0' || input[i] != ' '))
	{
		if ((input[i] == '"' || input[i] == '\'') && !find_quote(input, i))
		{
			*quotes = input[i];
			while (input[++i] != '\0' && input[i] != *quotes)
				size++;
			if (input[i] == *quotes)
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

static void	fill_exec(char *executable, char *input, int *index, char quotes)
{
	int	i;
	
	i = 0;
	while (input[*index] == ' ')
		(*index)++;
	if (quotes != '\0')
	{
		(*index)++;
		while (input[*index] && input[*index] != quotes)
			executable[i++] = input[(*index)++];
		if (input[*index] == quotes)
			(*index)++;
	}
	else
	{
		while (input[*index] != '\0' && input[*index] != ' ')
			executable[i++] = input[(*index)++];
	}
	executable[i] = '\0';
}

char	*exec_split(char *input, int *index, int command_index, t_gen_data *data)
{
	char	*executable;
	char	quotes;
	int		i;
	int		size;

	i = *index;
	quotes = '\0';
	size = exec_size(input, i, &quotes);
	executable = malloc(sizeof(char) * size + 1);
	if (!executable)
		return (NULL);
	fill_exec(executable, input, index, quotes);
	if (data)
	{
		if (quotes == '"')
			data->quotes[command_index] = 1;
		else if (quotes == '\'')
			data->quotes[command_index] = 2;
	}
	return (executable);
}
