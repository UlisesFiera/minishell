/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:50:20 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 15:50:53 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *arg)
{
	int	count;

	count = 0;
	if (!arg)
		return (write(1, "(null)", 6));
	while (*arg)
	{
		count += write(1, arg, 1);
		arg++;
	}
	return (count);
}
