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

void	echo(t_gen_data *data, char **commands)
{
	int		i;

	(void)data;
	i = 1;
	while (commands[i])
	{
		write(1, commands[i], ft_strlen(commands[i]));
		if (!commands[i + 1])
			write(1, "\n", 1);
		i++;
	}
	exit(0);
}
