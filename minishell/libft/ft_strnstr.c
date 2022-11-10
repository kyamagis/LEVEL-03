/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:48:10 by smuramat          #+#    #+#             */
/*   Updated: 2021/12/13 22:34:52 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *tgt, const char *set, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*set == '\0' || set == NULL)
		return ((char *)tgt);
	while (i < len && tgt[i] != '\0')
	{
		j = 0;
		while (set[j] == tgt[i + j] && i + j < len)
		{
			if (set[j + 1] == '\0')
				return ((char *)tgt + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
