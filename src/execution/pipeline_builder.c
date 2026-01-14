/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:41:02 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/30 23:06:55 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_count(t_gen_data *data, int index)
{
	int	size;

	size = 1;
	while (data->executables[index] && data->executables[index]->type != PIPE)
	{
		if (data->executables[index]->type == ARG)
			size++;
		index++;
	}
	return (size);
}

void	argv_fill(t_command *command, t_gen_data *data, int index)
{
	int	size;
	int	cmd_pos;
	int	i;

	cmd_pos = index;
	index++;
	size = arg_count(data, index);
	index = cmd_pos;
	command->argv = malloc(sizeof(char *) * (size + 1));
	if (!command->argv)
		fatal_error(data, "malloc");
	command->argv[size] = NULL;
	i = 0;
	command->argv[i++] = ft_strdup(data->executables[cmd_pos++]->text);
	while (data->executables[cmd_pos]
		&& data->executables[cmd_pos]->type != PIPE)
	{
		if (data->executables[cmd_pos]->type == ARG)
			command->argv[i++] = ft_strdup(data->executables[cmd_pos]->text);
		cmd_pos++;
	}
	redir_assign(command, data, index);
}

t_command	*command_fill(t_gen_data *data, int index)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		fatal_error(data, "malloc");
	command->quote = data->executables[index]->quote;
	argv_fill(command, data, index);
	return (command);
}

t_command	**command_array_builder(
	t_command **command_array, t_gen_data *data, int size)
{
	int	i;
	int	j;

	if (size == 0)
	{
		command_array = ft_calloc(2, sizeof(t_command *));
		command_array[0] = malloc(sizeof(t_command));
		command_array[0]->argv = NULL;
		redir_assign(command_array[0], data, 0);
		return (command_array);
	}
	command_array = ft_calloc((size + 1), sizeof(t_command *));
	if (!command_array)
		fatal_error(data, "malloc");
	i = 0;
	j = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->type == COMMAND)
			command_array[j++] = command_fill(data, i);
		i++;
	}
	return (command_array);
}
