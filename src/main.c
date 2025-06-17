/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:08:06 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/17 18:24:56 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_gen_data *data, char **env)
{
	data->exit_status = 0;
	read_input(data, data->final_prompt, 1); // get the user input and add it to history
	if (data->input && *data->input != '\0' && !ft_is_only_spaces(data->input))
	{
		parse_input(data, env);
		if (data->exit_status == 0)
		{
			if (data->pipe_flag > 0 && data->exit_status == 0)
				exec_pipe(data, env);
			else if (data->exit_status == 0)
				exec_command(data, env);
		}
	}
	free_exec(data);
	remove_temps();
	data->pipe_flag = 0;
	data->pipe_index = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_gen_data	*data;
	(void)argc;
	(void)argv;

	data = malloc(sizeof(t_gen_data));
	init_data(data);
	signal(SIGINT, signal_handler); // we override the SIGINT (ctrl-c) functionallity with our own, so we can get a new prompt
	welcome_message(data);
	read_history(".user_history");
	while (data->input) // we loop until the input it's NULL on error or by pressing ctrl-d
		main_loop(data, env);
	write_history(".user_history");
	free_data(data);
	free(data);
	return (0);
}
