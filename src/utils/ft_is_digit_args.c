/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:11:10 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/28 20:20:12 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_digit_args(char *args)
{
	int	i;
	int	digit;

	i = 0;
	digit = 1;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			digit = 0;
		i++;
	}
	return (digit);
}
