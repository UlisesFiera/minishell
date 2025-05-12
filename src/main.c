/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:08:06 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/09 14:15:40 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	signal_handler(int signal)
{
	g_signal = signal;
	if (g_signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal = 0;
}

int	main(void)
{
	char	*input;

	input = malloc(sizeof(char));
	signal(SIGINT, signal_handler);
	read_history(".user_history");
	while (input)
	{
		input = prompt();
		if (input)
			parse_input(input);
	}
	write_history(".user_history");
	free(input);
	return (0);
}