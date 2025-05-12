/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:45:42 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/09 14:14:41 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*username;
	char	*symbol;
	char	*final_prompt;
	char	*input;

	username = getenv("USER");
	symbol = "> ";
	final_prompt = ft_strjoin(username, symbol);
	input = readline(final_prompt);
	if (!input)
		free(final_prompt);
	else
		add_history(input);
	return (input);
}