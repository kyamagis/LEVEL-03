/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:46:14 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/31 16:29:25 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*simulate_one_philosopher(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	size_t	i;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	i = 0;
	if (philo->philo_idx % 2 == 1)
		usleep(200);
	while (42)
	{
		if (think(data, philo, i) == -1)
			return (NULL);
		if (take_forks_and_eat(data, philo) == -1)
			return (NULL);
		if (sleep_philo(data, philo) == -1)
			return (NULL);
		i++;
	}
	return (NULL);
}
