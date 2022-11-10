/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:38:40 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:45:03 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

size_t	ft_strstr_idx(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	hay_len;
	size_t	nee_len;

	if (haystack == NULL)
		return (0);
	hay_len = ft_strlen(haystack);
	nee_len = ft_strlen(needle);
	if (hay_len < nee_len)
		return (0);
	if (needle[0] == '\0')
		return (ft_strlen(haystack));
	i = 0;
	while (i <= hay_len - nee_len)
	{
		if (ft_strncmp(&haystack[i], needle, nee_len) == 0)
			return (i);
		i++;
	}
	return (i);
}

/*int	main(void)
{
	//const char	str[] = "Hellow!";
	//const char	to_find[] = "loi";

	//printf("a%s\n", strnstr(NULL, NULL,0));
	printf("%s\n", strnstr("ab", "a",4));
	printf("%s\n", ft_strnstr("ab", "a",4));
	// printf("%s\n", strnstr(str, to_find, 20));
	// printf("%s\n", ft_strnstr(str, to_find, 20));
	// printf("%s\n", strnstr("", to_find,0));
	// printf("%s\n", ft_strnstr("", to_find,0));
	// printf("%s\n", strnstr("", "",0));
	// printf("%s\n", ft_strnstr("", "",0));

	// printf("\n");

	// printf("origin%s\n", strnstr(NULL, "2", 0));
	// printf("makeft%s\n", ft_strnstr(NULL, "2", 0));
}*/