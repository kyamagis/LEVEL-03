/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:12:17 by smuramat          #+#    #+#             */
/*   Updated: 2022/08/27 12:25:34 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_last(t_dlist *head, t_dlist *node)
{
	t_dlist	*last;

	last = head->prev;
	node->prev = last;
	node->next = head;
	last->next = node;
	head->prev = node;
}
