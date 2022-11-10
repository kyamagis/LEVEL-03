/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:05:31 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/04 11:11:14 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	determine_if_the_value_is_appropriate(\
		t_data *data, char **argv)
{
	data->num_of_philo = ato_positive_int(argv[1]);
	if (data->num_of_philo < 1 || 200 < data->num_of_philo)
		return (put_error(INVALID_NUM, argv[1]));
	data->death_time = ato_positive_int(argv[2]);
	if (data->death_time < 60)
		return (put_error(INVALID_NUM, argv[2]));
	data->eating_time = ato_positive_int(argv[3]);
	if (data->eating_time < 60)
		return (put_error(INVALID_NUM, argv[3]));
	data->sleeping_time = ato_positive_int(argv[4]);
	if (data->sleeping_time < 60)
		return (put_error(INVALID_NUM, argv[4]));
	data->must_eat_num = ato_positive_int(argv[5]);
	if (data->must_eat_num == -1)
		return (put_error(INVALID_NUM, argv[5]));
	memset(data->each_philo_eat_count, 0, sizeof(size_t) * 200);
	return (0);
}

static void	destroy_all_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]) != SUCCESS)
			put_error(NULL, DESTROY_FAILUR);
		i++;
	}
	if (pthread_mutex_destroy(&data->gp_mutex) != SUCCESS)
		put_error(NULL, DESTROY_FAILUR);
	if (pthread_mutex_destroy(&data->put_action) != SUCCESS)
		put_error(NULL, DESTROY_FAILUR);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || 6 < argc)
		return (put_error(NULL, USAGE));
	memset(&data, 0, sizeof(t_data));
	if (determine_if_the_value_is_appropriate(&data, argv) == ERROR)
		return (ERROR);
	if (data.must_eat_num == 0)
		return (0);
	if (init_data(&data) == ERROR)
		return (ERROR);
	if (data.num_of_philo == 1)
		case_of_a_philo(&data);
	else
		pthread_create_and_join(&data);
	destroy_all_mutex(&data);
	return (0);
}
