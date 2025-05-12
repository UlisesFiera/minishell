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

char	*exec_split(char *input, int *index)
{
	char			*executable;
	int				i;
	int				size;

	size = 0;
	i = *index;
	while (input[i] == ' ')
		i++;
	while (input[i] != '\0' && input[i] != ' ')
	{
		size++;
		i++;
	}
	executable = malloc(sizeof(char) * size + 1);
	if (!executable)
		return (NULL);
	size = 0;
	while (*index < i)
	{
		while (input[*index] == ' ')
			(*index)++;
		while (input[*index] != '\0' && input[*index] != ' ')
		{
			executable[size] = input[*index];
			(*index)++;
			size++;
		}
	}
	executable[size] = '\0';
	return (executable);
}

int	exec_count_function(char *input)
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
		while (input[i] != '\0' && input[i] != ' ')
			i++;
	}
	return (exec_count);
}

void	parse_input(char *input)
{
	char	**executables;
	int		exec_count;
	int		index;
	int		i;

	exec_count = exec_count_function(input);
	executables = malloc(sizeof(char *) * (exec_count + 1));
	if (!executables)
		return ;
	executables[exec_count] = NULL;
	index = 0;
	i = 0;
	while(i < exec_count)
	{
		executables[i] = exec_split(input, &index);
		printf("loop %i %s\n", i, executables[i]);
		i++;
	}
}
