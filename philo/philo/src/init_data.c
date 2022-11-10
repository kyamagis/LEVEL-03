/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:24:53 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/31 13:25:15 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != SUCCESS)
			return (put_error(NULL, MUTEX_FAILURE));
		i++;
	}
	if (pthread_mutex_init(&data->put_action, NULL) != SUCCESS)
		return (put_error(NULL, MUTEX_FAILURE));
	if (pthread_mutex_init(&data->gp_mutex, NULL) != SUCCESS)
		return (put_error(NULL, MUTEX_FAILURE));
	return (0);
}

int	init_data(t_data *data)
{
	if (mutex_init(data) == ERROR)
		return (ERROR);
	return (0);
}
