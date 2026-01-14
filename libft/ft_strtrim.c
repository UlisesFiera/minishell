/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:52:37 by ulfernan          #+#    #+#             */
/*   Updated: 2024/09/26 19:52:38 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	clean_beg(char const *s1, char const *set)
{
	int	beg;
	int	i;

	beg = 0;
	while (s1[beg])
	{
		i = 0;
		while (set[i] && s1[beg] != set[i])
			i++;
		if (set[i] == '\0')
			break ;
		beg++;
	}
	return (beg);
}

static int	clean_end(char const *s1, char const *set)
{
	int	end;
	int	i;

	end = 0;
	while (s1[end])
		end++;
	end--;
	while (end >= 0)
	{
		i = 0;
		while (set[i] && s1[end] != set[i])
			i++;
		if (set[i] == '\0')
			break ;
		end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		beg;
	int		end;
	char	*ptr;

	if (!s1)
		return (NULL);
	beg = clean_beg(s1, set);
	end = clean_end(s1, set);
	end = end - beg + 1;
	if (end <= 0)
		return (ft_substr("", 0, 0));
	ptr = ft_substr(s1, beg, end);
	return (ptr);
}

/*

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		l;
	char	*ptr;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0' && s1[i] != set[j])
			j++;
		if (set[j] == '\0')
			break ;
		i++;
	}
	l = 0;
	while (s1[l] != '\0')
		l++;
	l--;
	while (l >= 0)
	{
		j = 0;
		while (set[j] != '\0' && s1[l] != set[j])
			j++;
		if (set[j] == '\0')
			break ;
		l--;
	}
	l = l - i + 1;
	if (l <= 0)
		return (ft_substr("", 0, 0));
	ptr = ft_substr(s1, i, l);
	return (ptr);
}

*/