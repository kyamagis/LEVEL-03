/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:58 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/04 11:50:10 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	detect_death_or_over_specified_eat_num(t_data *data, \
													t_philo *philo)
{
	data->count_eaten_philo += 1;
	philo->eat_count = 0;
	if (data->num_of_philo == data->count_eaten_philo)
	{
		data->continue_or_end = END;
		pthread_mutex_unlock(&data->gp_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&data->gp_mutex);
	return (0);
}

static int	detect_death(t_data *data, t_philo *philo)
{
	data->continue_or_end = END;
	put_action(data, philo, DEATH);
	pthread_mutex_unlock(&data->gp_mutex);
	return (-1);
}

static int	one_philo_detect_death_or_over_specified_eat_num(\
							t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->gp_mutex);
	philo->current_time = get_mili_sec() - data->start_time;
	if ((size_t)data->death_time <= philo->current_time - \
									philo->last_start_eating_time)
		return (detect_death(data, philo));
	if (data->must_eat_num != -2 && philo->eat_count == data->must_eat_num)
		return (detect_death_or_over_specified_eat_num(data, philo));
	pthread_mutex_unlock(&data->gp_mutex);
	return (0);
}

static int	all_philo_detect_death_or_over_specified_eat_num(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->gp_mutex);
		if (data->continue_or_end == END)
		{	
			pthread_mutex_unlock(&data->gp_mutex);
			return (-1);
		}
		pthread_mutex_unlock(&data->gp_mutex);
		if (one_philo_detect_death_or_over_specified_eat_num(\
									data, &data->philo[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(200);
	while (42)
	{
		if (all_philo_detect_death_or_over_specified_eat_num(data) == -1)
			break ;
	}
	return (NULL);
}
