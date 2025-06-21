/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_executables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:39:09 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/21 19:57:26 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_calculation(int *i, char *quotes, int command_index, t_gen_data *data)
{
	int	size;

	size = 0;
	while (data->input[*i] && data->input[*i] != *quotes)
	{
		if (data->input[*i] == ' ' && *quotes == '\0')
			return (size);
		if (data->input[*i] == '\'' || data->input[*i] == '"')
		{
			if (data->input[*i + 1] == '\'' || data->input[*i + 1] == '"')
				data->cat_quotes[command_index] = 1;
			if (!find_quote(data->input, *i))
				return (size - 1);
		}
		else if (data->input[*i] == '|')
		{
			if (size == 0)
				size++;
			return (size);
		}
		size++;
		(*i)++;
	}
	return (size);
}

int	exec_size(int i, char *quotes, int command_index, t_gen_data *data)
{
	int	size;

	while (data->input[i] == ' ')
		i++;
	if (data->input[i] == '\'' || data->input[i] == '"')
		*quotes = data->input[i++];
	size = size_calculation(&i, quotes, command_index, data);
	if (data->input[i] != '\0')
	{
		if (*quotes != '\0'
			&& (data->input[i + 1] == '\'' || data->input[i + 1] == '"'))
			data->cat_quotes[command_index] = 1;
	}
	return (size);
}

static void	fill_unquoted(char *executable, char *input, int *index, int *i)
{
	while (input[*index] != '\0' && input[*index] != ' ')
	{
		if (input[*index] == '\'' || input[*index] == '"')
		{
			if (!find_quote(input, *index))
			{
				executable[*i] = '\0';
				return ;
			}
		}
		else if (input[*index] == '|')
		{
			executable[*i] = '\0';
			return ;
		}
		executable[(*i)++] = input[(*index)++];
	}
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
	else if (input[*index] == '|')
	{
		pipe_executable(index, executable);
		return ;
	}
	else
		fill_unquoted(executable, input, index, &i);
	executable[i] = '\0';
}

char	*exec_split(int *index, int command_index, t_gen_data *data)
{
	char	*executable;
	char	quotes;
	int		i;
	int		size;

	i = *index;
	quotes = '\0';
	size = exec_size(i, &quotes, command_index, data);
	executable = malloc(sizeof(char) * (size + 1));
	if (!executable)
		return (NULL);
	fill_exec(executable, data->input, index, quotes);
	if (data)
	{
		if (quotes == '"')
			data->quotes[command_index] = 1;
		else if (quotes == '\'')
			data->quotes[command_index] = 2;
	}
	//printf("exec %i is %s with size %i\n", command_index, executable, size);
	return (executable);
}
