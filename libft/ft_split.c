/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:16:39 by ulfernan          #+#    #+#             */
/*   Updated: 2024/10/08 15:57:18 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	sword(char const *s, char c, int i)
{
	int	l;

	l = 0;
	while (s[i])
	{
		while ((s[i] == c) && (s[i + 1] == c))
			i += 1;
		if (s[i] == c)
			return (l);
		i += 1;
		l++;
	}
	return (l);
}

static void	free_split(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**populate(char const *s, char c, char **split)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = sword(s, c, i);
			split[j] = ft_substr(s, i, len);
			if (!split[j])
			{
				free_split(split, j);
				return (NULL);
			}
			i = i + len;
			j++;
		}
		if (s[i] != '\0')
			i++;
	}
	split[j] = NULL;
	return (split);
}

static int	count_tokens(char const *s, char c)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*s)
	{
		if (*s != c && !in_token)
		{
			in_token = 1;
			count++;
		}
		else if (*s == c)
			in_token = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int			row;
	char		**split;

	if (s == NULL)
		return (NULL);
	row = count_tokens(s, c);
	split = malloc((row + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (populate(s, c, split));
}
