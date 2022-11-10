/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:26:17 by smuramat          #+#    #+#             */
/*   Updated: 2021/12/13 22:13:30 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	error(const char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i + j]))
		j++;
	if (j < 19)
		return (0);
	else if (j > 19)
		return (1);
	else if (ft_memcmp("9223372036854775807", str + i, 19) >= 0)
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	long		res;
	int			sign;
	size_t		i;

	res = 0;
	sign = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '-')
		sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (error(str + i))
		return (sign - 1);
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10;
		res += (int)str[i] - '0';
		i++;
	}
	if (sign == 1)
		return (-res);
	return (res);
}
