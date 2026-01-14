/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:54:39 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/15 20:08:39 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dealloc(t_list_line **list, t_list_line *clean_node, char *buf)
{
	t_list_line		*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->string);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node->string[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

void	copy_content(t_list_line *list, char *new_string)
{
	int		i;
	int		j;

	if (!list)
		return ;
	i = 0;
	while (list)
	{
		j = 0;
		while (list->string[j])
		{
			if (list->string[j] == '\n')
			{
				new_string[i++] = '\n';
				new_string[i] = '\0';
				return ;
			}
			new_string[i] = list->string[j];
			j++;
			i++;
		}
		list = list->next;
	}
	new_string[i] = '\0';
}

t_list_line	*lstlast(t_list_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	found_nl(t_list_line *list)
{
	int		i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->string[i] && i < BUFFER_SIZE)
		{
			if (list->string[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	len_sum(t_list_line *list)
{
	int		len;
	int		i;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->string[i] && list->string && i < BUFFER_SIZE)
		{
			if (list->string[i] == '\n')
			{
				len++;
				return (len);
			}
			len++;
			i++;
		}
		list = list->next;
	}
	return (len);
}

/*

->	In "len_sum" we check if the char pointed is "\n", because 
	in that case, we want to include it in the final line 
	returned. We gotta increase the len to include it later, 
	and return because we don't want the rest of the chars
	from that node.
-> "copy_content" just copies the content of the node into 
	the final string. When it founds the "\n", it adds it to 
	the string, adds a null at the end, and finishes.
	l->	The null adding outside the loop is just in case we 
		are at the EOF, where sometimes the text doesn't end 
		in a "\n".
		
*/