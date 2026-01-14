/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:29:24 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/29 15:48:41 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>

int	too_many_args(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static void	cd_print_error(char *path, char *msg)
{
	ft_putstr_fd("minishell: cd: \n", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(msg, 2);
}

static int	cd_error_handler(char *path)
{
	if (errno == EACCES)
		cd_print_error(path, ": Permission denied\n");
	else if (errno == ENOENT)
		cd_print_error(path, ": No such file or directory\n");
	else if (errno == ENOTDIR)
		cd_print_error(path, ": Not a directory\n");
	else if (errno == ENAMETOOLONG)
		cd_print_error(path, ": File name too long\n");
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (1);
}

int	cd_handler(char *path)
{
	if (chdir(path) != 0)
		return (cd_error_handler(path));
	return (0);
}

int	cd(char **commands)
{
	char	*path;

	if (too_many_args(commands))
		return (1);
	if (!commands[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		chdir(path);
		return (0);
	}
	else
	{
		path = commands[1];
		return (cd_handler(path));
	}
}
