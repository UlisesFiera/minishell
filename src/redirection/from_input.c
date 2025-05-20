/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:31:51 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 17:31:51 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_child(char *file, char *cmd_path, t_gen_data *data)
{
	int	fd;

	if (!cmd_path)
	{
		printf("couldn't find command: %s\n", data->executables[0]);
		free(cmd_path);
		exit(1);
	}
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
	{
		printf("couldn't open file: %s\n", file);
		free(cmd_path);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	exec_from_input(t_gen_data *data, int index, char *cmd_path)
{
	char	*file;

	file = data->executables[index + 1];
	input_child(file, cmd_path, data);
}
