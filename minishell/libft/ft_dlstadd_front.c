/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:15:17 by smuramat          #+#    #+#             */
/*   Updated: 2022/08/27 12:25:27 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist *head, t_dlist *node)
{
	t_dlist	*first;

	first = head->next;
	node->prev = head;
	node->next = first;
	head->next = node;
	first->prev = node;
}
