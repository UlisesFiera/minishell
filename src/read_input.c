/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:45:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/28 18:21:12 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

char	*read_input(t_gen_data *data)
{
	free(data->input);
	data->input = readline(data->final_prompt);
	if (!data->input) // readline returns NULL when the user presses ctrl-D, which terminates the shell
		return (NULL);
	else if (data->input && data->input[0] != '\0' 
				&& !is_only_spaces(data->input))
		add_history(data->input);
	return (data->input);
}
