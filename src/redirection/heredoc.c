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

void	collect_input(int *end, char *delimiter)
{
	char	*line;

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
	collect_input(end, delimiter);
	data->input_fd = end[0];
	close(end[1]);
}
