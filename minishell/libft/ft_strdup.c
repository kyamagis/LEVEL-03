/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:28:03 by smuramat          #+#    #+#             */
/*   Updated: 2021/12/13 22:16:16 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		src_len;
	char	*src_p;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		++src_len;
	src_p = (char *)malloc(sizeof(char) * src_len + 1);
	if (src_p == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		src_p[i] = src[i];
		i++;
	}
	src_p[i] = '\0';
	return (src_p);
}
