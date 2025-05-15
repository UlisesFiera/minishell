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

char	**array_cleaner_left(t_gen_data *data) // this gives us an array with everything until the special symbol
{
	char	**clean_array;
	char	*symbol;
	int		i; // where the symbol is, and hence the number of args
	int		j;

	symbol = "<;<<;>;>>;|";
	i = 0;
	while (!(ft_strnstr(symbol, data->executables[i], ft_strlen(symbol))))
		i++;
	clean_array = malloc(sizeof(char *) * (i + 1));
	clean_array[i] = NULL;
	j = 0;
	while (j < i)
	{
		clean_array[j] = data->executables[j];
		j++; 
	}
	return (clean_array);
}

char	**array_cleaner_right(t_gen_data *data, int optcode) // this gives us an array with everything from the special symbol
{
	char	**clean_array;
	char	*symbol;
	int		i;
	int		j;
	int		n;

	symbol = "<;<<;>;>>;|";
	i = 0;
	while (!(ft_strnstr(symbol, data->executables[i], ft_strlen(symbol))))
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

char	**array_cleaner(t_gen_data *data)
{
	char	**clean_array;
	char	**left_commands;
	char	**right_commands;
	int		size;
	int		i;

	left_commands = array_cleaner_left(data);
	right_commands = array_cleaner_right(data, 1);
	size = 0;
	i = 0;
	while (left_commands[i++])
		size++;
	i = 0;
	while (right_commands[i++])
		size++;
	clean_array = malloc(sizeof(char *) * (size + 1));
	clean_array[size] = NULL;
	i = 0;
	size = 0;
	while (left_commands[i])
		clean_array[size++] = left_commands[i++];
	i = 0;
	while (right_commands[i])
		clean_array[size++] = right_commands[i++];
	free_arrays(right_commands, left_commands);
	return (clean_array);
}