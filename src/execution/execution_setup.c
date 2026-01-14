/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:35:06 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/12 13:35:06 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	**command_pipeline(t_gen_data *data)
{
	t_command	**command_array;
	int			size;
	int			i;

	size = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->type == COMMAND)
			size++;
		i++;
	}
	command_array = NULL;
	command_array = command_array_builder(command_array, data, size);
	return (command_array);
}

void	pipe_count(t_gen_data *data)
{
	int	i;

	i = 0;
	data->pipe_count = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->type == PIPE)
			data->pipe_count++;
		i++;
	}
}

void	redir_parse(t_gen_data *data, int *index)
{
	if (*index > 0 && (data->executables[*index - 1]->type == REDIRECTOR
			|| data->executables[*index - 1]->type == PIPE))
	{
		syntax_error(data->executables[*index]->text, data, 1);
		return ;
	}
	if (data->executables[*index]->text[0] == '|')
		data->executables[(*index)++]->type = PIPE;
	else
	{
		(*index)++;
		if (!data->executables[*index])
		{
			syntax_error("\n", data, 0);
			return ;
		}
		else if (data->executables[*index]->text[0] == '|')
		{
			syntax_error("|", data, 1);
			return ;
		}
		data->executables[(*index)++]->type = TARGET;
	}
}

void	cmd_parse(t_gen_data *data)
{
	int	i;

	i = 0;
	while (data->executables[i] && data->exit_loop != 1)
	{
		if (data->executables[i]->type == REDIRECTOR)
			redir_parse(data, &i);
		else if (i > 0 && data->executables[i - 1]->type == TARGET)
		{
			data->executables[i++]->type = ARG;
			while (data->executables[i]
				&& data->executables[i]->type == WORD)
				data->executables[i++]->type = ARG;
		}
		else if (data->executables[i]->type == WORD)
		{
			data->executables[i++]->type = COMMAND;
			while (data->executables[i]
				&& data->executables[i]->type == WORD)
				data->executables[i++]->type = ARG;
		}
		else
			i++;
	}
}

void	execution_setup(t_gen_data *data, char **env)
{
	if (data->exit_loop != 0 || g_signal_status != 0)
		return ;
	cmd_parse(data);
	if (data->exit_loop == 0)
		pipe_count(data);
	if (data->exit_loop == 0)
		data->command_array = command_pipeline(data);
	if (data->exit_loop == 0)
		execution_stream(data->command_array, data, env);
}
