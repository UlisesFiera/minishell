/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:08:06 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/22 10:12:50 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	reset_prompt(void)
{
	printf("\n");
	rl_on_new_line(); // this tells the readline lib that the cursor where it will start reading from is on a new line
	rl_replace_line("", 0); // clears the readline buffer that stores the input
	rl_redisplay();  // redraws the prompt
}

void	signal_handler(int signal)
{
	g_signal = signal;
	if (g_signal == SIGINT)
		reset_prompt();
	g_signal = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_gen_data	*data;
	(void)argc;
	(void)argv;

	data = malloc(sizeof(t_gen_data));
	init_data(data);
	signal(SIGINT, signal_handler); // we override the SIGINT (ctrl-c) functionallity with our own, so we can get a new prompt
	read_history(".user_history");
	while (data->input) // we loop until the input it's NULL on error or by pressing ctrl-d
	{
		read_input(data); // get the user input and add it to history
		if (data->input && *data->input != '\0')
		{
			parse_input(data, env);
			generate_heredocs(data);
			if (data->pipe_flag > 0)
				exec_pipe(data, env);
			else
				exec_command(data, env);
		}
		free_exec(data);
		remove_temps(data);
		data->pipe_flag = 0;
		data->pipe_index = 0;
	}
	write_history(".user_history");
	free_data(data);
	free(data);
	return (0);
}
