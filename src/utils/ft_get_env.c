/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:17:21 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/13 13:17:21 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *env_name, char **env)
{
	int		i;
	int		j;
	char	*env_sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		env_sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(env_sub, env_name) == 0)
		{
			free(env_sub);
			return (env[i] + j + 1);
		}
		free(env_sub);
		i++;
	}
	return (NULL);
}
