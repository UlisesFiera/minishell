/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:48:35 by ulfernan          #+#    #+#             */
/*   Updated: 2024/09/26 19:48:36 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cast1;
	unsigned char	*cast2;
	size_t			i;

	cast1 = (unsigned char *)s1;
	cast2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*cast1 != *cast2)
			return (*cast1 - *cast2);
		i++;
		cast1++;
		cast2++;
	}
	return (0);
}
