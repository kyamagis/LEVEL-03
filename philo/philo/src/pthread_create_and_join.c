/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create_and_join.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:25:38 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/02 20:13:44 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_one_philo(t_data *data, t_philo *philo, int i)
{
	philo->philo_idx = i;
	philo->eat_count = 0;
	philo->last_start_eating_time = 0;
	philo->death_time = (size_t)data->death_time;
	philo->eating_time = (size_t)data->eating_time;
	philo->sleeping_time = (size_t)data->sleeping_time;
	philo->right_fork = &data->fork[i];
	philo->left_fork = &data->fork[(i + 1) % data->num_of_philo];
	philo->data = data;
}

static void	create_philos_and_monitor(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		init_one_philo(data, &data->philo[i], i);
		if (pthread_create(&data->philo_tid[i], NULL, \
			simulate_one_philosopher, (void *)&data->philo[i]) != SUCCESS)
			put_error(NULL, CREATE_FAILURE);
		i++;
	}
	if (pthread_create(&data->monitor_tid, NULL, \
			monitor, (void *)data) != SUCCESS)
		put_error(NULL, CREATE_FAILURE);
}

static void	join_philos_and_monitor(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor_tid, NULL) != SUCCESS)
		put_error(NULL, JOIN_FAILUR);
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->philo_tid[i], NULL) != SUCCESS)
			put_error(NULL, JOIN_FAILUR);
		i++;
	}
}

void	pthread_create_and_join(t_data *data)
{
	create_philos_and_monitor(data);
	join_philos_and_monitor(data);
}
