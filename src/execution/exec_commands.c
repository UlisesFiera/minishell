/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:20:15 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 08:14:29 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_command(t_command *command, t_gen_data *data, char **env)
{
	int		status;
	char	*builtin;

	status = 0;
	if (!command->argv)
	{
		status = execute_env_command(command, data, env);
		return (status);
	}
	builtin = builtin_finder(command->argv[0]);
	if (data->pipe_count > 0)
	{
		if (builtin)
			status = builtin_handler(command->argv[0], command, data, env);
		else
			status = execve_handler(command, env);
		return (status);
	}
	if (builtin)
		status = execute_builtin(command->argv[0], command, data, env);
	else
		status = execute_env_command(command, data, env);
	return (status);
}

void	execution_stream(t_command **commands, t_gen_data *data, char **env)
{
	if (data->pipe_count > 0)
		pipeline_stream(commands, data, env);
	else
		data->last_exit_status = execute_command(commands[0], data, env);
}
