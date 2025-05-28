/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:24:20 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/28 18:38:03 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_gen_data *data)
{
	int	i;

	i = 0;
	if (data->executables)
	{
		while (data->executables[i])
		{
			free(data->executables[i]);
			i++;
		}
		free(data->executables);
		data->executables = NULL;
	}
	data->pipe_flag = 0;
}

void	remove_temps(t_gen_data *data)
{
	int	i;

	i = 0;
	if (data->tmp_filenames)
	{
		while (data->tmp_filenames[i])
		{
			unlink(data->tmp_filenames[i]);
			free(data->tmp_filenames[i]);
			data->tmp_filenames[i] = NULL;
			i++;
		}
		free(data->tmp_filenames);
		data->tmp_filenames = NULL;
	}
}

void	free_data(t_gen_data *data)
{
	if (data->final_prompt)
	{
		free(data->final_prompt);
		data->final_prompt = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tmp_fds)
	{
		free(data->tmp_fds);
		data->tmp_fds = NULL;
	}
}
