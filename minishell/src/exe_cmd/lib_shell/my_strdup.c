/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:54:34 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:45:08 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

char	*my_strdup(const char *s1)
{
	char	*prc;
	size_t	lens1;

	if (s1 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	if (lens1 == SIZE_MAX)
		return (NULL);
	prc = (char *)malloc(sizeof(char) * (lens1 + 1));
	if (prc == NULL)
		ft_exit(MALLOC_FAILURE);
	ft_strlcpy(prc, s1, lens1 + 1);
	return (prc);
}

/*int main(void)
{
    char *src = "hello";
    printf("%s\n", ft_strdup(src));
    printf("%s\n", strdup(src));

    char *src1 = "";
    printf("%s\n", ft_strdup(src1));
    printf("%s\n", strdup(src1));

	char *src2 = NULL;
    printf("%s\n", ft_strdup(src2));
    printf("%s\n", strdup(src2));
}*/