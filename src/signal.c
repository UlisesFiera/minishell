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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(int signum)
{
	if (signum == SIGINT && isatty(0) && g_in_secondary_prompt == 0)
		reset_prompt();
	if (signum == SIGINT && isatty(0) && g_in_secondary_prompt == 1)
		close(0);
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
