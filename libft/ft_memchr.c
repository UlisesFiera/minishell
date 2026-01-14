/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:48:19 by ulfernan          #+#    #+#             */
/*   Updated: 2024/09/26 19:48:20 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cast;
	size_t			i;

	cast = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*cast == (unsigned char)c)
		{
			return (cast);
		}
		cast++;
		i++;
	}
	return (NULL);
}
