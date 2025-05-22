/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:24:20 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/21 19:25:09 by ulfernan         ###   ########.fr       */
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
	while (data->tmp_filenames[i])
	{
		unlink(data->tmp_filenames[i]);
		i++;
	}
	free(data->tmp_filenames);
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
}