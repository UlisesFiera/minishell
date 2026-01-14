/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:31:20 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 17:31:20 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_setup(t_gen_data *data, int findex, char **delimiter, int index)
{
	*delimiter = data->executables[index]->text;
	data->tmp_filenames[findex] = file_name_generator(findex, data);
	data->tmp_fds[findex] = open(
			data->tmp_filenames[findex], O_CREAT | O_RDWR, 0644);
	if (data->tmp_fds[findex] == -1)
		fatal_error(data, "fd");
}

void	collect_input(t_gen_data *data, int index, int findex, char **env)
{
	char	*delimiter;
	char	*line;

	heredoc_setup(data, findex, &delimiter, index);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			heredoc_error(data, delimiter);
			return ;
		}
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!ft_strcmp(line, delimiter))
			break ;
		line = expand_heredoc(data, index, env, &line);
		write(data->tmp_fds[findex], line, ft_strlen(line));
		write(data->tmp_fds[findex], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
}

void	generate_heredocs(t_gen_data *data, char **env)
{
	int	i;
	int	count;

	i = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->type == DELIMITER)
			data->heredoc_count++;
		i++;
	}
	data->tmp_fds = malloc(sizeof(int) * (data->heredoc_count + 1));
	if (!data->tmp_fds)
		fatal_error(data, "malloc");
	data->tmp_fds[data->heredoc_count] = INULL;
	data->tmp_filenames = ft_calloc((data->heredoc_count + 1), sizeof(char *));
	if (!data->tmp_filenames)
		fatal_error(data, "malloc");
	i = 0;
	count = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->type == DELIMITER)
			collect_input(data, i, count++, env);
		i++;
	}
}
