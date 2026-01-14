/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:24:20 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 14:09:02 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_gen_data *data)
{
	int	i;

	i = 0;
	if (data->executables)
	{
		while (data->executables[i])
		{
			if (data->executables[i]->text)
			{
				free(data->executables[i]->text);
				data->executables[i]->text = NULL;
			}
			free(data->executables[i]);
			data->executables[i] = NULL;
			i++;
		}
		free(data->executables);
		data->executables = NULL;
	}
}

void	free_command_loop(t_command **commands, int i)
{
	int	j;

	if (commands[i]->argv)
		ft_free_tab(&commands[i]->argv);
	if (commands[i]->redirections)
	{
		j = 0;
		while (commands[i]->redirections[j])
		{
			if (commands[i]->redirections[j]->target_file)
			{
				free(commands[i]->redirections[j]->target_file);
				commands[i]->redirections[j]->target_file = NULL;
			}
			free(commands[i]->redirections[j]);
			commands[i]->redirections[j] = NULL;
			j++;
		}
		free(commands[i]->redirections);
		commands[i]->redirections = NULL;
	}
}

void	free_commands(t_command ***commands)
{
	int	i;

	i = 0;
	while ((*commands)[i])
	{
		free_command_loop(*commands, i);
		free((*commands)[i]);
		(*commands)[i] = NULL;
		i++;
	}
	free(*commands);
	*commands = NULL;
}

void	free_input_fp_fds(t_gen_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->final_prompt)
	{
		free(data->final_prompt);
		data->final_prompt = NULL;
	}
	if (data->tmp_fds)
	{
		free(data->tmp_fds);
		data->tmp_fds = NULL;
	}
}

void	free_data(t_gen_data *data)
{
	free_input_fp_fds(data);
	if (data->exec_env)
		ft_free_tab(&data->exec_env);
	if (data->exec_env_export)
		ft_free_tab(&data->exec_env_export);
	if (data->command_array)
		free_commands(&data->command_array);
	if (data->pipe_ends != NULL)
		free(data->pipe_ends);
	if (data->executables)
		free_tokens(data);
	free_heredoc(data);
}
