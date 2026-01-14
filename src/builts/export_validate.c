/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:40:39 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/29 20:17:34 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_first_char_valid(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

static int	is_valid_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_')
		return (1);
	return (0);
}

static int	print_invalid_identifier(char *var)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (1);
}

int	check_valid_var_name(char *var)
{
	int	i;

	if (!var || !*var)
	{
		ft_putstr_fd("minishell: export: `': not a valid identifier\n", 2);
		return (1);
	}
	if (!is_first_char_valid(var[0]))
		return (print_invalid_identifier(var));
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!is_valid_char(var[i]))
			return (print_invalid_identifier(var));
		i++;
	}
	return (0);
}
