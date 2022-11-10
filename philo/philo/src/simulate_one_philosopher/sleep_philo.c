/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:46:37 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/02 13:56:28 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	sleep_philo(t_data *data, t_philo *philo)
{
	return (put_action_and_usleep(philo, data, SLEEP, philo->sleeping_time));
}
