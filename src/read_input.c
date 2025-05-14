/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:45:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/14 11:01:56 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(t_gen_data *data)
{
	free(data->input);
	data->input = readline(data->final_prompt);
	if (!data->input) // readline returns NULL when the user presses ctrl-D, which terminates the shell
		return (NULL);
	else
		add_history(data->input);
	return (data->input);
}
