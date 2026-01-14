/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:46:48 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 18:46:48 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_count(t_gen_data *data)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir("./tmp");
	if (!dir)
		return ;
	entry = readdir(dir);
	data->heredoc_count = 0;
	while ((entry))
	{
		if (ft_strncmp(
				entry->d_name, "heredoc_tmp_", ft_strlen("heredoc_tmp_")) == 0)
			data->heredoc_count++;
		entry = readdir(dir);
	}
	closedir(dir);
}

char	*expand_heredoc(t_gen_data *data, int index, char **env, char **line)
{
	char	*tmp;

	if (data->executables[index]->quote != SINGLE)
	{
		tmp = *line;
		*line = expansion_setup(data, *line, env);
		free(tmp);
		return (*line);
	}
	return (*line);
}

char	*file_name_generator(int findex, t_gen_data *data)
{
	char	*file_prefix;
	char	*file_sufix;
	char	*final;

	file_prefix = "tmp/heredoc_tmp_";
	file_sufix = ft_itoa(findex);
	if (!file_sufix)
		fatal_error(data, "malloc");
	final = ft_strjoin(file_prefix, file_sufix);
	if (!final)
		fatal_error(data, "malloc");
	free(file_sufix);
	return (final);
}
