/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/05/28 12:49:24 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/28 12:49:24 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	n_check(t_command *command, int *i)
{
	char	*n;
	int		flag;
	int		j;

	flag = 0;
	n = command->argv[*i];
	j = 0;
	if (n[j] != '-')
		return (flag);
	j++;
	if (!n[j])
		return (flag);
	while (n[j])
	{
		if (n[j] != 'n')
			return (flag);
		j++;
	}
	flag = 1;
	(*i)++;
	return (flag);
}

int	echo(t_gen_data *data, t_command *command)
{
	int	jump;
	int	i;

	i = 1;
	if (!command->argv[i])
	{
		write(1, "\n", 1);
		data->last_exit_status = 0;
		return (data->last_exit_status);
	}
	jump = n_check(command, &i);
	while (command->argv[i])
	{
		write(1, command->argv[i], ft_strlen(command->argv[i]));
		if (!command->argv[i + 1] && !jump)
			write(1, "\n", 1);
		else if (command->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	data->last_exit_status = 0;
	return (data->last_exit_status);
}
