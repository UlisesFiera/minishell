/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:22:28 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 10:23:09 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cursor;

	if (lst == NULL || new == NULL)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		cursor = *lst;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
}

/*

->	We just traverse the list and add a node at the last next. 
	The reason why we get the double pointer is for us to
	be able to put new at the head of the list in the case 
	the list is empty, thus modifying "lst". The traversing
	could be done with just the actual pointer.

*/