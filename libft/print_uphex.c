/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uphex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:50:26 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 15:50:51 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_uphex(long arg, int base)
{
	int		count;
	char	*symbol;

	symbol = "0123456789ABCDEF";
	base = 16;
	if (arg < 16)
		return (print_char(symbol[arg]));
	else
	{
		count = print_uphex(arg / base, base);
		return (count + print_uphex(arg % base, base));
	}
}
