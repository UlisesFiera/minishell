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

void	parse_input(t_gen_data *data, char **env)
{
	int		exec_count;
	int		index;
	int		i;

	exec_count = exec_counter(data->input);
	data->executables = malloc(sizeof(char *) * (exec_count + 1));
	if (!data->executables)
		return ;
	data->executables[exec_count] = NULL;
	init_quotes(data, exec_count);
	index = 0;
	i = 0;
	while (i < exec_count)
	{
		data->executables[i] = exec_split(data->input, &index, i, data);
		i++;
	}
	env_var_check(data, env);
	set_pipe_flag(data);
}
