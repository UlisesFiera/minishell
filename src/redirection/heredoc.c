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

	data->executable_pos = find_executable(data);
	if (data->executable_pos < 0)
	{
		data->exit_status = 1;
		return ;
	}
	delimiter = data->executables[index + 1];
	data->tmp_filenames[count] = file_name_generator(count);
	data->tmp_fds[count] = open(data->tmp_filenames[count], O_CREAT | O_RDWR, 0644);
	line = readline("> ");
	if (!line)
	{
		printf("-minishell: warning: here-document at line %i delimited by end-of-file (wanted %s) heredoc %i\n", data->lineno, delimiter, count);
		return ;
	}
	if (data->quotes[index + 1] != 2)
		line = parse_env_vars(data, line, env);
	while (line && ft_strcmp(line, delimiter))
	{
		write(data->tmp_fds[count], line, ft_strlen(line));
		write(data->tmp_fds[count], "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
		{
			line = delimiter;
			printf("-minishell: warning: here-document at line %i delimited by end-of-file (wanted %s) heredoc %i\n", data->lineno, delimiter, count);
			return ;
		}
		if (data->quotes[index + 1] != 2)
			line = parse_env_vars(data, line, env);
	}
	close(data->tmp_fds[count]);
	data->tmp_fds[count] = open(data->tmp_filenames[count], O_RDONLY, 0644); // must close again in free data
	free(line);
}

void	exec_heredoc(t_gen_data *data, int index, int count)
{
	(void)index;
	(void)count;
	int	i;
	int	final_fd;

	if (!data->tmp_fds)
		exit(0);
	i = 0;
	while (data->tmp_fds[i] != -1)
		i++;
	final_fd = data->tmp_fds[i - 1];
	i = 0;
	while (data->tmp_fds[i] != final_fd)
	{
		close(data->tmp_fds[i]);
		i++;
	}
	dup2(final_fd, 0);
	count++;
}
