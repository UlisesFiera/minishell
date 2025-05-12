/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:47:54 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/12 09:52:38 by ulfernan         ###   ########.fr       */
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

void	*init_data(t_gen_data *data)
{
	data->input = malloc(sizeof(char *));
	if (!data->input)
		return (NULL);
	if (!load_username(data))
		return (NULL);
	return (data);
}