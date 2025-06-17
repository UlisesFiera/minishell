/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:57:06 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/17 15:57:06 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line(); // this tells the readline lib that the cursor where it will start reading from is on a new line
	rl_replace_line("", 0); // clears the readline buffer that stores the input
	rl_redisplay();  // redraws the prompt
}

void	signal_handler(int signum)
{
	if (signum == SIGINT && isatty(0))
		reset_prompt();
}

void	signal_handler_redir(int signum)
{
	if (signum == SIGINT && isatty(0))
	{
		write(1, "\n", 1);
		signal(SIGINT, SIG_DFL);
		kill(getpid(), SIGINT);
	}
}