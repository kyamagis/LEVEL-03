/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:38:51 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/02 16:38:40 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	think(t_data *data, t_philo *philo, size_t i)
{
	pthread_mutex_lock(&data->gp_mutex);
	if (philo->philo_idx == 0 && i == 0)
		data->start_time = get_mili_sec();
	if (philo->philo_idx % 2 == 0 && i == 0 && \
		philo->philo_idx + 1 != data->num_of_philo)
	{	
		pthread_mutex_unlock(&data->gp_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->gp_mutex);
	return (put_action_and_usleep(philo, data, THINK, 0));
}
