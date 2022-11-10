/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 22:26:45 by smuramat          #+#    #+#             */
/*   Updated: 2021/11/26 22:26:54 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *src, char const *set)
{
	size_t	front;
	size_t	rear;
	char	*str;

	str = 0;
	if (src != 0 && set != 0)
	{
		front = 0;
		rear = ft_strlen(src);
		while (src[front] && ft_strchr(set, src[front]))
			front++;
		while (src[rear - 1] && ft_strchr(set, src[rear - 1]) && rear > front)
			rear--;
		str = (char *)malloc(sizeof(char) * (rear - front + 1));
		if (str)
			ft_strlcpy(str, src + front, rear - front + 1);
	}
	return (str);
}
