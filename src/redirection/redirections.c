/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:56:49 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 16:56:49 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_handler(t_gen_data *data, char *redirection, int index)
{
	if (!ft_strcmp(data->executables[i], "<"))
		exec_to_input(data, index);
	else if (!ft_strcmp(data->executables[i], ">"))
		exec_to_output(data, index);
	else if (!ft_strcmp(data->executables[i], "<<"))
		exec_append(data, index);
	else if (!ft_strcmp(data->executables[i], ">>")) 
		exec_here(data, index);
}

int	redirect_check(t_gen_data *data)
{
	int		i;

	i = 0;
	while (data->executables[i])
	{
		if (!ft_strcmp(data->executables[i], "<") 
			|| !ft_strcmp(data->executables[i], ">")
			|| !ft_strcmp(data->executables[i], "<<") 
			|| !ft_strcmp(data->executables[i], ">>"))
		{
			redirect_handler(data, data->executables[i], i);
			return (1);
		}
		i++;
	}
	return (0);
}