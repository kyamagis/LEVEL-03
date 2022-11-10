/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:00:58 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/04 11:28:53 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	put_action(t_data *data, t_philo *philo, int action_num)
{
	if (action_num == EAT)
	{
		printf("%ld %d%s\n", philo->time_stamp, \
				philo->philo_idx + 1, TAKEN_A_FORK);
		printf("%ld %d%s\n", philo->time_stamp, \
				philo->philo_idx + 1, TAKEN_A_FORK);
		printf("%ld %d%s\n", philo->time_stamp, philo->philo_idx + 1, EATING);
		philo->last_start_eating_time = philo->time_stamp;
	}
	else if (action_num == SLEEP)
	{	
		printf("%ld %d%s\n", philo->time_stamp, philo->philo_idx + 1, SLEEPING);
		data->each_philo_eat_count[philo->philo_idx]++;
		philo->eat_count++;
	}
	else if (action_num == THINK)
		printf("%ld %d%s\n", philo->time_stamp, philo->philo_idx + 1, THINKING);
	else if (action_num == DEATH)
		printf("\x1b[31m%ld %d%s\033[m\n", \
		philo->current_time, philo->philo_idx + 1, DIED);
}
