/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of_a_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:00:30 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/02 14:00:42 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	a_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->gp_mutex);
	data->start_time = get_mili_sec();
	pthread_mutex_lock(&data->fork[philo->philo_idx]);
	pthread_mutex_lock(&data->put_action);
	printf("%d %d%s\n", 0, 1, TAKEN_A_FORK);
	pthread_mutex_unlock(&data->put_action);
	pthread_mutex_unlock(&data->gp_mutex);
	pthread_mutex_unlock(&data->fork[philo->philo_idx]);
	while (42)
	{
		pthread_mutex_lock(&data->gp_mutex);
		if (data->continue_or_end == END)
			break ;
		pthread_mutex_unlock(&data->gp_mutex);
	}
	pthread_mutex_unlock(&data->gp_mutex);
}

static void	*simulate_a_philosopher(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	a_philo(data, philo);
	return (NULL);
}

static void	init_a_philo(t_data *data, t_philo *philo)
{
	philo->philo_idx = 0;
	philo->eat_count = 0;
	philo->last_start_eating_time = 0;
	philo->data = data;
}

void	case_of_a_philo(t_data *data)
{
	init_a_philo(data, &data->philo[0]);
	if (pthread_create(&data->philo_tid[0], NULL, \
		simulate_a_philosopher, (void *)&data->philo[0]) != SUCCESS)
		put_error(NULL, CREATE_FAILURE);
	if (pthread_create(&data->monitor_tid, NULL, \
			monitor, (void *)data) != SUCCESS)
		put_error(NULL, CREATE_FAILURE);
	if (pthread_join(data->monitor_tid, NULL) != SUCCESS)
		put_error(NULL, JOIN_FAILUR);
	if (pthread_join(data->philo_tid[0], NULL) != SUCCESS)
		put_error(NULL, JOIN_FAILUR);
}
