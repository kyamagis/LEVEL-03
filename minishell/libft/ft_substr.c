/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:14:25 by smuramat          #+#    #+#             */
/*   Updated: 2021/12/13 09:45:46 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*src_p;

	if (!src)
		return (NULL);
	if ((size_t)start >= ft_strlen(src) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(src) < len)
		src_p = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	else
		src_p = (char *)malloc(sizeof(char) * (len + 1));
	if (!src_p)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (i >= start && j < len)
			src_p[j++] = src[i];
		i++;
	}
	src_p[j] = 0;
	return (src_p);
}
