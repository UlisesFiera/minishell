/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:20:55 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 16:20:55 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*builtin_finder(char *executable)
{
	if (!ft_strcmp(executable, "echo"))
		return ("echo");
	else if (!ft_strcmp(executable, "cd"))
		return ("cd");
	else if (!ft_strcmp(executable, "env"))
		return ("env");
	else if (!ft_strcmp(executable, "exit"))
		return ("exit");
	else if (!ft_strcmp(executable, "export"))
		return ("export");
	else if (!ft_strcmp(executable, "pwd"))
		return ("pwd");
	else if (!ft_strcmp(executable, "unset"))
		return ("unset");
	else
		return (NULL);
}

int	execve_handler(t_command *command, char **env)
{
	char	*cmd_path;
	int		status;

	if (!command->argv)
		return (0);
	if (command->argv[0][0] && (command->argv[0][0] == '/'
		|| command->argv[0][0] == '.'))
		cmd_path = ft_strdup(command->argv[0]);
	else
		cmd_path = ft_get_path(command->argv[0], env);
	if (!cmd_path)
		return (exec_error(command, &cmd_path, 0));
	status = execve(cmd_path, command->argv, env);
	if (status == -1)
		return (exec_error(command, &cmd_path, 1));
	return (status);
}

int	builtin_handler(
		char *builtin, t_command *command, t_gen_data *data, char **env_list)
{
	if (!ft_strcmp(builtin, "echo"))
		return (echo(data, command));
	else if (!ft_strcmp(builtin, "cd"))
		return (cd(command->argv));
	else if (!ft_strcmp(builtin, "env"))
		return (env(env_list));
	else if (!ft_strcmp(builtin, "exit"))
		return (exit_minishell(data, command->argv));
	else if (!ft_strcmp(builtin, "export"))
		return (export(data, command->argv, data->exec_env_export));
	else if (!ft_strcmp(builtin, "pwd"))
		return (pwd(data));
	else if (!ft_strcmp(builtin, "unset"))
		return (unset(data, command->argv));
	else
		return (-1);
}
