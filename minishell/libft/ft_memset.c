/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:52:27 by smuramat          #+#    #+#             */
/*   Updated: 2021/11/19 19:53:32 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	unsigned char	*buf_p;
	unsigned char	c;

	c = (unsigned char)ch;
	buf_p = (unsigned char *)buf;
	while (n--)
		*buf_p++ = c;
	return (buf);
}
