/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_executables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:39:09 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/14 17:49:18 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_size(char *input, int i, char *quotes)
{
	int	size;

	size = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\'' || input[i] == '"')
	{
		*quotes = input[i];
		i++;
	}
	while (input[i] && input[i] != ' ' && input[i] != *quotes)
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (!find_quote(input, i))
				return (size - 1);
		}
		size++;
		i++;

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
		{
			if (input[*index] == '\'' || input[*index] == '"')
			{
				if (!find_quote(input, *index))
				{
					executable[i] = '\0';
					return ;
				}
			}
			executable[i++] = input[(*index)++];
		}
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
