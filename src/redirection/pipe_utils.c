/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:36:00 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/20 19:36:00 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pipe_flag(t_gen_data *data)
{
	int	i;

	i = 0;
	while (data->executables[i])
	{
		if (!strcmp(data->executables[i], "|"))
		{
			if (i == 0)
			{
				syntax_error(data->executables[i], data);
				return ;
			}
			else
				data->pipe_flag++;
		}
		i++;
	}
}

int	pipe_index(t_gen_data *data, char **commands)
{
	if (!commands[data->pipe_index])
		return (data->pipe_index);
	if (commands[data->pipe_index][0] == '|')
		data->pipe_index++;
	while (commands[data->pipe_index])
	{
		if (commands[data->pipe_index][0] == '|')
			return (data->pipe_index);
		data->pipe_index++;
	}
	return (data->pipe_index);
}

char	**executables_copy(t_gen_data *data)
{
	char	**copy;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (data->executables[i])
	{
		size++;
		i++;
	}
	copy = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (data->executables[i])
	{
		copy[i] = ft_strdup(data->executables[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	pipe_executable(int *index, char *executable)
{
	executable[0] = '|';
	executable[1] = '\0';
	(*index)++;
}
