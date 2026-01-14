/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:04:22 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 10:18:23 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned int	uz_strlen(const char *str)
{
	unsigned int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

static unsigned int	uz_strnlen(const char *str, unsigned int size)
{
	unsigned int	len;

	len = 0;
	while (len < size && *str)
	{
		len++;
		str++;
	}
	return (len);
}

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	space;
	unsigned int	index;

	index = 0;
	dest_len = uz_strnlen(dest, size);
	src_len = uz_strlen(src);
	if (dest_len == size)
	{
		return (size + src_len);
	}
	space = size - dest_len - 1;
	while (index < space && src[index] != '\0')
	{
		dest[dest_len + index] = src[index];
		index++;
	}
	dest[dest_len + index] = '\0';
	return (dest_len + src_len);
}

/*

Previamente creamos un strlen y un strlen para facilitar el conteo de los strings
y la comparación con un size, y ahorrar líneas.

1. Primero comprobamos directamente si el tamaño de destino es mayor 
   o menor que el size.
   Si el size es menor, directamente devolvemos src + size porque es lo que
   tendría que medir el buffer de dest para que cupiera el src.
2. Si hay suficiente hueco en destino, primero comprobamos el hueco restante
   que nos deja size para copiar descontando el tamaño de dest, teniendo en
   cuenta que hay que dejar 1 hueco para el nulo final. 
3. Concatenamos durante el space disponible. Usamos índices para poder copiar
   desde un punto concreto, en este caso, el final de dest.
4. Devolvemos el tamaño de ambas fuentes juntas. Es útil en el caso de que
   no hayamos podido copiar todo, para saber cuánto aumentar el size. 

int main (void)
{
    char dest[50] = "Hola, ";
    char src[] = "mundo";
    unsigned int size = 12;
    int value;

    value = ft_strlcat(dest, src, size);
    printf("Return = %i\n", value);
    printf("Cat = %s\n", dest);
}

*/