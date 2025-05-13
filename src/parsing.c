/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:40:35 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/09 13:40:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_closing_quote(char *input, int index) // we check if the quote is grouping a command or if it's single
{
	while (input[index])
	{
		if (input[index] == '"')
			return (0);
		index++;
	}
	return (1);
}

int	exec_size()

char	*exec_split(char *input, int *index)
{
	char	*executable;
	int		quotes;
	int		i;
	int		size;

	size = 0;
	i = *index;
	quotes = 0;
	while (input[i] == ' ')
		i++;
	while (input[i] != '\0' && input[i] != ' ' && !quotes)
	{
		if (input[i] == '"')
		{
			if (!find_closing_quote(input, i + 1))
			{
				quotes = 1;
				i++;
				while (input[i] != '\0' && input[i] != '"')
				{
					size++;
					i++;
				}
			}
		}
		else
		{
			size++;
			i++;
		}
	}
	executable = malloc(sizeof(char) * size + 1);
	if (!executable)
		return (NULL);
	size = 0;
	while (*index < i)
	{
		while (input[*index] == ' ')
			(*index)++;
		if (quotes)
		{
			(*index)++;
			while (input[*index] != '\0' && input[*index] != '"')
			{
				executable[size] = input[*index];
				(*index)++;
				size++;
			}
			executable[size] = '\0';
			return (executable);
		}
		else if (!quotes)
		{
			while (input[*index] != '\0' && input[*index] != ' ')
			{
				executable[size] = input[*index];
				(*index)++;
				size++;
			}
		}
	}
	executable[size] = '\0';
	return (executable);
}

int	exec_counter(char *input)
{
	int		exec_count;
	int		i;

	exec_count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] != '\0')
			exec_count++;
		if (input[i] != '"')
		{
			if (!find_closing_quote(input, i + 1))
			{
				while (input[i] != '\0' && input[i] != '"')
					i++;
			}
		}
		while (input[i] != '\0' && input[i] != ' ')
			i++;
	}
	return (exec_count);
}

void	parse_input(t_gen_data *data)
{
	int		exec_count;
	int		index;
	int		i;

	exec_count = exec_counter(data->input);
	data->executables = malloc(sizeof(char *) * (exec_count + 1));
	if (!data->executables)
		return ;
	data->executables[exec_count] = NULL;
	index = 0;
	i = 0;
	while(i < exec_count)
	{
		data->executables[i] = exec_split(data->input, &index);
		printf("%s\n", data->executables[i]);
		i++;
	}
}
