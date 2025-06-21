/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:49:24 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/28 12:49:24 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **commands)
{
	int	jump;
	int	i;

	jump = 0;
	i = 1;
	while (commands[i])
	{
		if (!ft_strcmp(commands[i], "-n"))
		{
			i++;
			jump = 1;
		}
		write(1, commands[i], ft_strlen(commands[i]));
		if (!commands[i + 1] && !jump)
			write(1, "\n", 1);
		else if (commands[i + 1])
			write(1, " ", 1);
		i++;
	}
	exit(0);
}
