/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:40:31 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/27 21:00:57 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_gen_data *data)
{
	char	*working_dir;
	char	*fallback;

	working_dir = malloc(sizeof(char) * (PATH_MAX + 1));
	if (!working_dir)
		fatal_error(data, "malloc");
	if (getcwd(working_dir, PATH_MAX) == NULL)
	{
		free(working_dir);
		fallback = ft_strdup(getenv("OLDPWD"));
		if (!fallback)
			return (1);
		working_dir = ft_strdup(fallback);
		if (!working_dir)
			fatal_error(data, "malloc");
	}
	printf("%s\n", working_dir);
	free(working_dir);
	return (0);
}
