/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:36:35 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/30 16:54:57 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(char **env)
{
	int	n;

	n = 0;
	while (env && env[n])
		n++;
	return (n);
}

int	cmp_env_name(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((char)s1[i] - (char)s2[i]);
		i++;
	}
	if ((s1[i] == '\0' || s1[i] == '=') && (s2[i] == '\0' || s2[i] == '='))
	{
		return (0);
	}
	if (s1[i] == '\0')
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}

void	sort_export(char **env)
{
	int		i;
	int		j;
	int		n;
	char	*temp;

	i = 1;
	n = env_len(env);
	while (i < n)
	{
		temp = env[i];
		j = i;
		while (j > 0 && cmp_env_name(temp, env[j - 1]) < 0)
		{
			env[j] = env[j - 1];
			j--;
		}
		env[j] = temp;
		i++;
	}
}
