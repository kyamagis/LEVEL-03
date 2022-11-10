/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:58:46 by kyamagis          #+#    #+#             */
/*   Updated: 2022/04/25 09:49:33 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_isdigit(int c)
{
	return (('0' <= c) && (c <= '9'));
}

/*#include <stdio.h>
int	main(void)
{
	printf("%d", ft_isdigit('1'));
	printf("%d", ft_isdigit('0'));
	printf("%d", ft_isdigit('a'));
	return (0);
}*/