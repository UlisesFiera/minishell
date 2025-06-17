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

#include "../minishell.h"

void	free_arrays(char **right_commands, char **left_commands)
{
	free(right_commands);
	free(left_commands);
}

char	**pipe_divider(char **commands, int index)
{
	char	**clean_array;
	int		size;
	int		i;
	int		j;

	i = index - 1; // we skip the | or \0 moving to the left as we will copy from there to the left
	size = 0;
	while (i >= 0 && commands[i] && commands[i][0] != '|')
	{
		size++;
		i--;
	}
	clean_array = malloc(sizeof(char *) * (size + 1));
	if (!clean_array)
		return (NULL);
	i = index - size;
	j = 0;
	while (j < size)
	{
		clean_array[j] = ft_strdup(commands[i]);
		i++;
		j++;
	}
	clean_array[j] = NULL;
	return (clean_array);
}

int	command_count_without_symbols(t_gen_data *data, char *symbol)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
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
	return (count);
}

char	**array_cleaner_left(t_gen_data *data) // we get an array with everything but redirectors, until pipe
{
	char	**clean_array;
	char	*symbol;
	int		count;
	int		i;
	int		j;

	symbol = "<;<<;>;>>";
	count = command_count_without_symbols(data, symbol);
	clean_array = malloc(sizeof(char *) * (count + 1));
	clean_array[count] = NULL;
	i = 0;
	j = 0;
	while (data->executables[i])
	{
		if (j >= count)
			return (clean_array);
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
