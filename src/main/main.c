/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:08:06 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 12:45:45 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal_status = 0;

void	main_loop(t_gen_data *data, char **env)
{
	reset_data(data);
	env = data->exec_env;
	read_input(data, data->final_prompt, 1);
	if (data->input && *data->input != '\0'
		&& !ft_is_only_spaces(data->input))
	{
		if (g_signal_status == 130)
		{
			data->prev_exit_status = g_signal_status;
			g_signal_status = 0;
		}
		parse_input(data);
		expand_token(data, env);
		field_split(data);
		execution_setup(data, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_gen_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_gen_data));
	if (!data)
		fatal_error(data, "malloc");
	init_data(data, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	welcome_message();
	read_history(".user_history");
	while (data->input)
		main_loop(data, env);
	exit_handler(data, data->last_exit_status);
	return (0);
}
