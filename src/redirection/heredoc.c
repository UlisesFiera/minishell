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

char	*parse_env_vars_heredoc(char *line, char **env, t_gen_data *data)
{
	int		count;
	int		i;
	int		j;
	char	**env_paths;
	char	*new_string;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count++;
		i++;
	}
	if (count == 0)
		return (line);
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			env_paths[j] = env_cleaner(line + i + 1, env, data, line);
			if (!env_paths[j])
			{
				free(env_paths);
				return (line);
			}
			new_string = ft_strinsert(line, env_paths[j], i, 2);
			line = new_string;
			j++;
		}
		i++;
	}
	return (line);
}

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
	if (data->quotes[index + 1] != 2)
		line = parse_env_vars_heredoc(line, env, data);
	while (line && ft_strcmp(line, delimiter))
	{
		write(data->tmp_fds[count], line, ft_strlen(line));
		write(data->tmp_fds[count], "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(data->tmp_fds[count]);
	data->tmp_fds[count] = open(data->tmp_filenames[count], O_RDONLY, 0644); // must close again in free data
	free(line);
}

void	exec_heredoc(t_gen_data *data, int index, int count)
{
	(void)index;

	dup2(data->tmp_fds[count], 0);
	count++;
}






/*
void	collect_input(int *end, char *delimiter, t_gen_data *data)
{
	char	*line;
	int		tty;

	tty = open("/dev/tty", O_RDWR);
	data->input_fd = dup(0); // we save stdin and stdout to restore them after this execution
	data->output_fd = dup(1);
	dup2(tty, 0);
	dup2(tty, 1);
	close(tty);
	line = readline("> ");
	while (line && ft_strcmp(line, delimiter))
	{
		write(end[1], line, ft_strlen(line));
		write(end[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
}

void	exec_heredoc(t_gen_data *data, int index, char *cmd_path)
{
	char	*delimiter;
	int		end[2];

	if (!cmd_path)
	{
		printf("couldn't find command: %s\n", data->executables[0]);
		free(cmd_path);
		exit(1);
	}
	delimiter = data->executables[index + 1];
	pipe(end);
	collect_input(end, delimiter, data);
	close(end[1]);
	data->input_fd = end[0]; 
}

*/