/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:05:04 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/16 17:05:04 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_finder(char **command_array)
{
	int	index;

	index = 0;
	while (command_array[index])
	{
		if (access(command_array[index], F_OK) == 0)
			return (index);
		index++;
	}
	return (-1);
}