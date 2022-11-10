/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:18:09 by smuramat          #+#    #+#             */
/*   Updated: 2022/08/27 12:29:34 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstdel_back(t_dlist *head)
{
	t_dlist	*last;

	if (head->prev == head)
		return (NULL);
	last = head->prev;
	head->prev = last->prev;
	last->prev->next = head;
	last->next = last;
	last->prev = last;
	return (last);
}
