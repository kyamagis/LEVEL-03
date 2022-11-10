/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mili_sec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:18:14 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/31 14:23:07 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

size_t	get_mili_sec(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (put_error(NULL, "gettimeofday_error"));
	return ((1000 * tv.tv_sec) + (tv.tv_usec / 1000));
}

/* int main(void)
{
	struct timeval	tv;
	size_t			time;

	time = get_mili_sec(&tv);
	printf("time = %ld\ntime = %ld\n", time, tv.tv_sec);
} */
