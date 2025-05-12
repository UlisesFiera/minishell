/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:45:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/12 09:22:33 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(t_gen_data *data)
{
	char	*input;

	input = readline(data->final_prompt);
	if (!input) // readline returns NULL when the user presses ctrl-D, which terminates the shell
		free_data(data);
	else
		add_history(input);
	return (input);
}