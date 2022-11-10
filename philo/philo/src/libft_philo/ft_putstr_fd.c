/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:58:44 by kyamagis          #+#    #+#             */
/*   Updated: 2022/05/12 11:09:33 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	ft_putchr_len(int fd, char *s, size_t len)
{
	write(fd, s, len);
	s += len;
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	ft_putchr_len(fd, s, len % INT_MAX);
	len /= INT_MAX;
	while (len--)
		ft_putchr_len(fd, s, INT_MAX);
}

/*int	main(void)
{
	char s[] = "abc";

	ft_putstr_fd(s, 1);
	return (0);

	size_t	ft_putstr_fd(char *s, int fd)
	{
		size_t	i;

		if (s == NULL)
		return ;
		i = 0;
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
		return (i);
	}
}*/
