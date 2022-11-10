/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:31:06 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:45:14 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

char	*my_substr(char const *s, size_t start, size_t len)
{
	char	*substr;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (my_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	if (len == SIZE_MAX)
		return (NULL);
	substr = (char *)malloc (sizeof (char) * (len + 1));
	if (substr == NULL)
		ft_exit(MALLOC_FAILURE);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}

/*
char	*ft_putisnull(char const *str, size_t size)
{
	size_t	i;
	char *addr;

	addr =(char *)str;
	i = 0;
	while (i < size)
	{
		if (addr[i] == '\0')
			addr[i] = '0';
		i++;
	}
	return (addr);
}
int main(void)
{
	char const s[] = "ABCDEFGH";
	unsigned int start = 0;
	size_t len = 0;

	printf("[printsubstr]%s\n", ft_substr("tripouille", 100, 1));
	printf("[exchangesub]%d\n",!strcmp(ft_substr("tripouille", 100, 1), ""));
}*/
