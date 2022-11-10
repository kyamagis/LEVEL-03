/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_time_stamp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:48:54 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/04 11:50:33 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	detect_one_philo_death(t_data *data, t_philo *philo)
{
	data->continue_or_end = END;
	put_action(data, philo, DEATH);
	return (-1);
}

static int	detect_over_must_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (data->each_philo_eat_count[i] < data->must_eat_num)
			return (0);
		i++;
	}
	data->continue_or_end = END;
	return (-1);
}

int	update_time_stamp(t_data *data, t_philo *philo)
{
	philo->time_stamp = get_mili_sec() - data->start_time;
	if (data->continue_or_end == END)
		return (-1);
	if (philo->death_time <= philo->time_stamp - philo->last_start_eating_time)
		return (detect_one_philo_death(data, philo));
	if (data->must_eat_num == -2)
		return (0);
	return (detect_over_must_eat(data));
}
