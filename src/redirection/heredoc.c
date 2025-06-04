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

char	*file_name_generator(int count)
{
	char	*file_prefix;
	char	*file_sufix;
	char	*final;

	file_prefix = "tmp/heredoc_tmp_";
	file_sufix = ft_itoa(count);
	final = ft_strjoin(file_prefix, file_sufix);
	free(file_sufix);
	return (final);
}

void	collect_input(t_gen_data *data, int index, int count, char **env)
{
	char	*delimiter;
	char	*line;

	delimiter = data->executables[index + 1];
	data->tmp_filenames[count] = file_name_generator(count);
	data->tmp_fds[count] = open(data->tmp_filenames[count], O_CREAT | O_RDWR, 0644);
	line = readline("> ");
	if (!line)
		return ;
	if (data->quotes[index + 1] != 2)
		line = parse_env_vars(data, line, env);
	while (line && ft_strcmp(line, delimiter))
	{
		write(data->tmp_fds[count], line, ft_strlen(line));
		write(data->tmp_fds[count], "\n", 1);
		free(line);
		line = readline("> ");
		line = parse_env_vars(data, line, env);
	}
	close(data->tmp_fds[count]);
	data->tmp_fds[count] = open(data->tmp_filenames[count], O_RDONLY, 0644); // must close again in free data
	free(line);
}

void	exec_heredoc(t_gen_data *data, int index, int count)
{
	(void)index;

	if (!data->tmp_fds)
		exit(0);
	dup2(data->tmp_fds[count], 0);
	count++;
}
