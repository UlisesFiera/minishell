/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:36:34 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/14 12:36:34 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arrays(char **right_commands, char **left_commands)
{
	free(right_commands);
	free(left_commands);
}

void	fill_arrays(char **clean_array, char **left_cmd, char **right_cmd)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (left_cmd[i])
		clean_array[size++] = left_cmd[i++];
	i = 0;
	while (right_cmd[i])
		clean_array[size++] = right_cmd[i++];
	free_arrays(right_cmd, left_cmd);
}

char	**array_cleaner_left(t_gen_data *data) // we get an array with everything but redirectors, until pipe
{
	char	**clean_array;
	char	*symbol;
	int		count;
	int		i;
	int		j;

	symbol = "<;<<;>;>>";
	count = 0;
	i = 0;
	while (data->executables[i] && data->executables[i][0] != '|')
	{
		while (ft_strnstr(symbol, data->executables[i], ft_strlen(symbol))) // we skip 2 because whats right after a symbol is always a file, hence not a valid arg for the command
			i += 2;
		if ((data->executables[i]))
		{
			count++;
			i++;
		}
	}
	clean_array = malloc(sizeof(char *) * (count + 1));
	clean_array[count] = NULL;
	i = 0;
	j = 0;
	while (i < count)
	{
		while (ft_strnstr(symbol, data->executables[i], ft_strlen(symbol)))
			i += 2;
		clean_array[j] = data->executables[i];
		i++;
		j++; 
	}
	return (clean_array);
}

char	**array_cleaner_right(t_gen_data *data, int optcode, char *symbol) // this gives us an array with everything from the special symbol
{
	char	**clean_array;
	int		i;
	int		j;
	int		n;

	i = 0;
	while (ft_strcmp(symbol, data->executables[i]))
		i++;
	i++;
	if (optcode == 1) //optcode will be 1 when the first arg after the symbol is a file, in that case we skip it
		i++;
	n = i;
	j = 0;
	while (data->executables[i++])
		j++;
	clean_array = malloc(sizeof(char *) * (j + 1));
	clean_array[j] = NULL;
	i = 0;
	while (data->executables[n])
		clean_array[i++] = data->executables[n++];
	while (data->executables[n])
		clean_array[i++] = data->executables[n++];
	return (clean_array);
}

/*
char	**array_cleaner(t_gen_data *data, char *symbol)
{
	char	**clean_array;
	char	**left_commands;
	char	**right_commands;
	int		size;
	int		i;

	left_commands = array_cleaner_left(data, symbol);
	right_commands = array_cleaner_right(data, 1, symbol);
	size = 0;
	i = 0;
	while (left_commands[i++])
		size++;
	i = 0;
	while (right_commands[i++])
		size++;
	clean_array = malloc(sizeof(char *) * (size + 1));
	clean_array[size] = NULL;
	fill_arrays(clean_array, left_commands, right_commands);
	return (clean_array);
}
*/