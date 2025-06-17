/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:31:44 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 17:31:44 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_child(char *file, char *cmd_path, t_gen_data *data)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf("-minishell: %s: No such file or directory\n", file);
		free(cmd_path);
		exit(1);
	}
	if (!cmd_path)
	{
		printf("couldn't find command: %s\n", data->executables[data->executable_pos]);
		free(cmd_path);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	exec_to_output(t_gen_data *data, int index, char *cmd_path)
{
	char	*file;

	file = data->executables[index + 1];
	output_child(file, cmd_path, data);
}
