/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:22:40 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 10:23:09 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/*

->  "**lst" points to the memory adress of "*lst". "*lst" 
	points to the memory adress of a "head". 
	l-> We use a pointer to the pointer because by 
		derefencing we can modify the value that "**lst" points to. 
		And what's that value? The memory adress that "*lst" 
		points to. And that's what we want to do.
->  "next" expects a pointer to a node. The "next" node of 
	"new" has to be the current "head". So we wanna assign it a pointer
	to the current head.
	l-> "*lst" is the value stored in the memory 
		address that "**lst" points to. That value is a 
		pointer to the current head.
		l-> "**lst" would be the value stored in 
			the memory pointed hy the pointer we point to; 
			in this case, that'd be the node itself.
->  We modify the value that "**lst" is pointing to. 
	The value is a pointer to "head". 
	We change it to a pointer to "new".

*/