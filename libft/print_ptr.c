/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:50:18 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 15:50:48 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert_ptr(unsigned long address)
{
	int		count;
	char	*symbol;

	count = 0;
	symbol = "0123456789abcdef";
	if (address < 16)
		return (print_char(symbol[address]));
	else
	{
		count += convert_ptr(address / 16);
		return (count + print_char(symbol[address % 16]));
	}
}

int	print_ptr(void *arg)
{
	unsigned long	adress;
	int				count;

	if (arg == 0)
		return (write(1, "(nil)", 5));
	count = 0;
	adress = (unsigned long)arg;
	count = write(1, "0x", 2);
	count += convert_ptr(adress);
	return (count);
}
