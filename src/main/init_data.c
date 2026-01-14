/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:03:08 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/30 20:42:07 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_data(t_gen_data *data)
{
	free_heredoc(data);
	if (data->executables)
		free_tokens(data);
	if (data->command_array)
		free_commands(&data->command_array);
	data->command_array = NULL;
	if (data->pipe_ends != NULL)
		free(data->pipe_ends);
	data->pipe_ends = NULL;
	if (data->tmp_fds)
	{
		free(data->tmp_fds);
		data->tmp_fds = NULL;
	}
	data->tmp_fds = NULL;
	data->exec_count = 0;
	data->pipe_flag = 0;
	data->token_index = 0;
	data->env_size = 0;
	data->heredoc_count = 0;
	data->redir_count = 0;
	data->exp_token_size = 0;
	data->prev_exit_status = data->last_exit_status;
	data->exit_loop = 0;
}

void	init_data(t_gen_data *data, char **env)
{
	data->input = ft_strdup("");
	if (!data->input)
		fatal_error(data, "malloc");
	data->input[0] = '\0';
	load_username(data);
	data->token_index = 0;
	data->tmp_filenames = NULL;
	data->tmp_fds = NULL;
	data->executables = NULL;
	data->pipe_ends = NULL;
	data->exit_loop = 0;
	data->last_exit_status = 0;
	data->lineno = 0;
	data->env_size = 0;
	data->prev_exit_status = 0;
	data->command_array = NULL;
	data->redir_count = 0;
	data->exp_token_size = 0;
	load_env(data, env);
	load_export(data, env);
}
