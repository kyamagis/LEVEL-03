/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:04:45 by smuramat          #+#    #+#             */
/*   Updated: 2021/11/24 10:01:02 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_p;
	const unsigned char	*src_p;

	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	i = 0;
	if (!dst_p && !src_p)
		return (NULL);
	if (src_p < dst_p)
		while (++i <= n)
			dst_p[n - i] = src_p[n - i];
	else
		while (n-- > 0)
			*(dst_p++) = *(src_p++);
	return (dst);
}
