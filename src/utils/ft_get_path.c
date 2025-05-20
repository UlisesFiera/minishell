/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:02:53 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 13:02:53 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_exec(char **all_dir, char *cmd)
{
	int		i;
	char	*path;
	char	*exec;

	i = 0;
	while (all_dir[i])
	{
		path = ft_strjoin(all_dir[i], "/");
		exec = ft_strjoin(path, cmd);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(all_dir);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_tab(all_dir);
	return (NULL);
}

char	*ft_get_path(char *cmd, char **env)
{
	char	**all_dir;

	all_dir = ft_split(ft_getenv("PATH", env), ':');
	return (find_exec(all_dir, cmd));
}