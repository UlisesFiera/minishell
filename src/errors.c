/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:32:58 by ulfernan          #+#    #+#             */
/*   Updated: 2025/06/05 20:45:32 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    syntax_error(char *token, t_gen_data *data)
{
    printf("syntax error near unexpected token '%s'", token);
    data->exit_status = 2;
}