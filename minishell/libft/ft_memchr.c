/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:45:21 by smuramat          #+#    #+#             */
/*   Updated: 2021/12/01 10:08:30 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	search_c;

	str = (unsigned char *)s;
	search_c = (unsigned char)c;
	i = 0;
	while (i++ < n)
	{
		if (*str == search_c)
			return (str);
		str++;
	}
	return (NULL);
}
