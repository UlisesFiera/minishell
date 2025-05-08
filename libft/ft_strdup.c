/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:04:01 by ulfernan          #+#    #+#             */
/*   Updated: 2024/09/27 16:47:24 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	uz_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

char	*ft_strdup(char *src)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (uz_strlen(src) + 1));
	if (copy == 0)
		return (0);
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/* 

1. Creamos strlen para medir la longitud del string que nos pasen.
2. Llamamos a malloc para comprobar si hay suficiente memoria. Si no, NULO.
3. Calculamos 1 hueco extra para el null de la nueva cadena en nuestro strlen.
4. Copiamos.

*/
