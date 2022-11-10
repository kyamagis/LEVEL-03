/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:49:49 by kyamagis          #+#    #+#             */
/*   Updated: 2022/05/11 15:45:42 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

/*int main(void)
{
	ft_putchar_fd('c', 1);
}*/