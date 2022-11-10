/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:16:40 by smuramat          #+#    #+#             */
/*   Updated: 2022/08/27 12:29:02 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstdel_front(t_dlist *head)
{
	t_dlist	*first;

	if (head->next == head)
		return (NULL);
	first = head->next;
	head->next = first->next;
	first->next->prev = head;
	first->next = first;
	first->prev = first;
	return (first);
}
