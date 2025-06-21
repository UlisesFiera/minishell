/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:47:54 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/21 15:58:02 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quotes(t_gen_data *data, int exec_count)
{
	int	i;

	data->quotes = malloc(sizeof(int) * (exec_count));
	data->cat_quotes = malloc(sizeof(int) * (exec_count));
	i = 0;
	while (i < exec_count)
	{
		data->quotes[i] = 0;
		data->cat_quotes[i] = 0;
		i++;
	}
}

void	generate_heredocs(t_gen_data *data, char **env)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (data->executables[i])
	{
		if (!ft_strcmp(data->executables[i], "<<"))
			count++;
		i++;
	}
	data->tmp_fds = malloc(sizeof(int) * (count + 1));
	data->tmp_filenames = malloc(sizeof(char *) * (count + 1));
	data->tmp_filenames[count] = NULL;
	data->tmp_fds[count] = -1;
	i = 0;
	count = 0;
	while (data->executables[i])
	{
		if (!ft_strcmp(data->executables[i], "<<"))
			collect_input(data, i, count++, env);
		i++;
	}
}

void	*load_username(t_gen_data *data)
{
	char	*symbol;
	char	*colored_username;
	char	*tmp;

	data->username = getenv("USER");
	colored_username = ft_strjoin(GREEN, data->username);
	if (!colored_username)
		return (NULL);
	symbol = "> ";
	tmp = ft_strjoin(colored_username, symbol);
	if (!tmp)
		return (NULL);
	free(colored_username);
	data->final_prompt = ft_strjoin(tmp, RESET);
	free(tmp);
	if (!data->final_prompt)
		return (NULL);
	return (data);
}

void	*init_data_handler(t_gen_data *data)
{
	data->input = ft_strdup("");
	if (!data->input)
		return (NULL);
	data->input[0] = '\0';
	if (!load_username(data))
		return (NULL);
	data->tmp_filenames = NULL;
	data->tmp_fds = NULL;
	data->executables = NULL;
	data->exec_copy = NULL;
	data->pipe_flag = 0;
	data->input_fd = -1;
	data->output_fd = -1;
	data->pipe_index = 0;
	data->exit_status = 0;
	data->last_exit_status = 0;
	data->lineno = 0;
	return (data);
}

void	init_data(t_gen_data *data)
{
	if (!data)
		exit(1);
	if (!init_data_handler(data))
	{
		free_data(data);
		free(data);
		exit(1);
	}
}
