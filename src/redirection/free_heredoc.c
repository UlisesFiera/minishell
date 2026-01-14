/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:24:51 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 18:01:27 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_temps(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*full_path;

	dir = opendir("./tmp");
	if (!dir)
		return ;
	entry = readdir(dir);
	while ((entry))
	{
		if (strncmp(entry->d_name, "heredoc_tmp_", 12) == 0)
		{
			full_path = ft_strjoin("./tmp/", entry->d_name);
			unlink(full_path);
			free(full_path);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

void	free_tmp_filenames(t_gen_data *data)
{
	int	i;

	i = 0;
	if (data->tmp_filenames)
	{
		while (data->tmp_filenames[i])
		{
			free(data->tmp_filenames[i]);
			data->tmp_filenames[i++] = NULL;
		}
		free(data->tmp_filenames);
		data->tmp_filenames = NULL;
	}
}

void	close_fds(t_gen_data *data)
{
	int	i;

	if (data->tmp_fds)
	{
		i = 0;
		while (data->tmp_fds[i] != INULL)
			close(data->tmp_fds[i++]);
	}
}

void	free_heredoc(t_gen_data *data)
{
	close_fds(data);
	free_tmp_filenames(data);
	remove_temps();
}
