/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:14:45 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:45:00 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*suc1;
	const unsigned char	*suc2;

	suc1 = (const unsigned char *)s1;
	suc2 = (const unsigned char *)s2;
	i = 0;
	while ((suc1[i] - suc2[i]) == 0 && \
			suc1[i] && suc2[i])
	{
		i++;
	}
	return (suc1[i] - suc2[i]);
}

/*int	main(void)
{
	size_t	n = 3;
	const char s1m[] = "ABAE" ;
	const char s2m[] = "ABZJE";
	const char s10[] = "ABCd" ;
	const char s20[] = "ABC";
	const char s1p[] = "ABCDE" ;
	const char s2p[] = "ABB";

	printf("本家%d\n", strcmp(s1m, s2m));
	printf("自作%d\n\n", ft_strcmp(s1m, s2m));

	printf("本家%d\n", strcmp(s10, s20));
	printf("自作%d\n\n", ft_strcmp(s10, s20));

	printf("本家%d\n", strcmp(s1p, s2p));
	printf("自作%d\n", ft_strcmp(s1p, s2p));
}*/
