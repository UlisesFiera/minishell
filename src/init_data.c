/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:47:54 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 16:03:08 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*load_username(t_gen_data *data)
{
	char	*symbol;

	data->username = getenv("USER");
	symbol = "> ";
	data->final_prompt = ft_strjoin(data->username, symbol);
	if (!data->final_prompt)
		return (NULL);
	return (data);
}

void	*init_data_handler(t_gen_data *data)
{
	data->input = ft_strdup("");
	if (!data->input)
		return (NULL);
	data->input[0] = '\0'; 
	if (!load_username(data))
		return (NULL);
	data->executables = NULL;
	data->pipe_flag = 0;
	return (data);
}

void	init_data(t_gen_data *data)
{
	if (!data)
		exit(1);
	if (!init_data_handler(data))
	{
		free_data(data);
		free(data);
		exit(1);
	}
}
