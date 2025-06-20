/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:24:20 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/19 16:22:47 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tmp_filenames(t_gen_data *data)
{
	int	i;

	i = 0;
	if (data->tmp_filenames)
	{
		while (data->tmp_filenames[i])
			free(data->tmp_filenames[i++]);
		free(data->tmp_filenames);
	}
	free(data->tmp_fds);
}

void	free_exec(t_gen_data *data)
{
	int	i;

	i = 0;
	if (data->executables)
	{
		while (i < data->exec_count)
		{
			if (data->executables[i])
				free(data->executables[i]);
			i++;
		}
		free(data->executables);
		data->executables = NULL;
	}
}

void	remove_temps()
{
	DIR 			*dir;
	struct dirent	*entry;
	char			*full_path;

	dir = opendir("./tmp");
	if (!dir)
		return ;
	while ((entry = readdir(dir)))
	{
		if (strncmp(entry->d_name, "heredoc_tmp_", 12) == 0)
		{
			full_path = ft_strjoin("./tmp/", entry->d_name);
			unlink(full_path);
			free(full_path);
		}
	}
	closedir(dir);
}

void	free_data(t_gen_data *data)
{
	if (data->final_prompt)
	{
		free(data->final_prompt);
		data->final_prompt = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tmp_fds)
	{
		free(data->tmp_fds);
		data->tmp_fds = NULL;
	}
	if (data->exec_copy)
		ft_free_tab(data->exec_copy);
	free_exec(data);
}

void	reset_data(t_gen_data *data)
{
	if (data->quotes)
	{
		free(data->quotes);
		data->quotes = NULL;
	}
	data->pipe_flag = 0;
	data->pipe_index = 0;
}
