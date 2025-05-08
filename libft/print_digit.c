/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:50:15 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 15:50:46 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_digit(long arg, int base)
{
	int		count;
	char	*symbol;

	symbol = "0123456789abcdef";
	if (arg < 0)
	{
		write (1, "-", 1);
		return (print_digit(-arg, base) + 1);
	}
	else if (arg < base)
		return (print_char(symbol[arg]));
	else
	{
		count = print_digit(arg / base, base);
		return (count + print_digit(arg % base, base));
	}
}
