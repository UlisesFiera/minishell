/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:23:00 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 10:23:04 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*

->  Declare a POINTER to a "t_list" struct because 
	we want to store the values into the heap.
	l-> That means we want to store the values and 
		use them when we exit the function. 
		Otherwise they would be erased after we exit it, 
		missing the whole purpose of a list.
	l-> Because we want that, we need to tell the heap 
		how much memory it needs for my "t_list" 'cause is a
		personalised variable.
->  Because we are working with a pointer, we assign the 
	values using "->" instead of ".".
->  We return the address that node points to, which 
	will be a full working node.
	
*/