/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:22:16 by smuramat          #+#    #+#             */
/*   Updated: 2021/12/01 10:09:41 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*target;
	char	finder;
	size_t	i;

	target = (char *)s;
	finder = (char)c;
	i = 0;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (target[i] == finder)
			return (target + i);
		i--;
	}
	if (target[i] == finder)
		return (target);
	return (NULL);
}
