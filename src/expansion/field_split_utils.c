/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:12:35 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/29 12:12:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	field_size(char *var_text, int *index, int *i_first)
{
	int	size;

	*index = skip_space_tab_nl_field(var_text, *index);
	*i_first = *index;
	size = 0;
	while (var_text[*index]
		&& var_text[*index] != ' ' && var_text[*index] != '\t'
		&& var_text[*index] != '\n')
	{
		size++;
		(*index)++;
	}
	return (size);
}

void	alloc_token(t_gen_data *data, t_token **exp_array, int i_new, int i_old)
{
	exp_array[i_new] = malloc(sizeof(t_token));
	if (!exp_array[i_new])
		fatal_error(data, "malloc");
	exp_array[i_new]->expand = data->executables[i_old]->expand;
	exp_array[i_new]->quote = data->executables[i_old]->quote;
	exp_array[i_new]->type = data->executables[i_old]->type;
	exp_array[i_new]->merge = data->executables[i_old]->merge;
}
