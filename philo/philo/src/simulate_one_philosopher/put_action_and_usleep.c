/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_action_and_usleep.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:36:31 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/31 16:41:07 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	usleep_to_specified_sec(size_t specified_sec)
{
	size_t	end_time;

	if (specified_sec == 0)
		return ;
	end_time = specified_sec + get_mili_sec();
	while (get_mili_sec() < end_time)
		usleep(100);
}

int	put_action_and_usleep(t_philo *philo, t_data *data, \
								int action_num, size_t specified_sec)
{
	pthread_mutex_lock(&data->gp_mutex);
	pthread_mutex_lock(&data->put_action);
	if (update_time_stamp(data, philo) == -1)
	{
		pthread_mutex_unlock(&data->put_action);
		pthread_mutex_unlock(&data->gp_mutex);
		return (-1);
	}
	put_action(data, philo, action_num);
	pthread_mutex_unlock(&data->put_action);
	pthread_mutex_unlock(&data->gp_mutex);
	usleep_to_specified_sec(specified_sec);
	return (0);
}
