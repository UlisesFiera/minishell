/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:40:35 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/09 13:40:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delimiter_check(t_gen_data *data, int index)
{
	if (index > 0 && (!ft_strcmp(data->executables[index - 1]->text, "<<")))
	{
		if (data->executables[index]->type == REDIRECTOR)
			syntax_error(data->executables[index]->text, data, 1);
		else
			data->executables[index]->type = DELIMITER;
	}
}

void	fill_exec_array(t_gen_data *data)
{
	int	i;

	i = 0;
	while (i < data->exec_count)
	{
		data->executables[i] = exec_split(data);
		delimiter_check(data, i);
		i++;
	}
}

void	parse_input(t_gen_data *data)
{
	if (data->exit_loop != 0)
		return ;
	exec_counter(data);
	data->executables = ft_calloc((data->exec_count + 1), sizeof(t_token *));
	if (!data->executables)
		fatal_error(data, "malloc");
	fill_exec_array(data);
}
