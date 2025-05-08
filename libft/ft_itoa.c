/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:48:02 by ulfernan          #+#    #+#             */
/*   Updated: 2024/09/26 19:48:05 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static char	*itoam(char *str, int digitsm, unsigned int un, int nm)
{
	str = malloc((digitsm + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[digitsm] = '\0';
	while (un > 0)
	{
		str[digitsm - 1] = (un % 10) + '0';
		un /= 10;
		digitsm--;
	}
	if (nm < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*itoa;
	int				digits;
	unsigned int	un;
	unsigned int	temp;

	digits = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		un = (unsigned int)-n;
		digits++;
	}
	else
		un = (unsigned int)n;
	temp = un;
	while (temp > 0)
	{
		temp /= 10;
		digits++;
	}
	itoa = NULL;
	return (itoa = itoam(itoa, digits, un, n));
}
