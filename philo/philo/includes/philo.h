/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:05 by kyamagis          #+#    #+#             */
/*   Updated: 2022/11/04 11:30:08 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USAGE "usage: ./philo <number_of_philosophers>\n\
		  <time_to_die>\n\
		   <time_to_eat>\n\
		    <time_to_sleep>\n\
			 <number_of_times_each_philosopher_must_eat>\n\
example: ./philo 1 800 200 200\n\
	 ./philo 5 800 200 200\n\
	 ./philo 5 800 200 200 7\n\
	 ./philo 4 410 200 200\n\
	 ./philo 4 310 200 100"

# define INVALID_NUM "Invalid number: "
# define MALLOC_FAILURE "Malloc failure"
# define MUTEX_FAILURE "Mutex failure"
# define CREATE_FAILURE "Pthread create failure"
# define JOIN_FAILUR "Join failure"
# define DESTROY_FAILUR "Destroy failure"

# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEATH 3

# define TAKEN_A_FORK " has taken a fork"
# define EATING " is eating"
# define SLEEPING " is sleeping"
# define THINKING " is thinking"
# define DIED " died"

# define CONTINUE 0
# define END 3

# define ERROR 1
# define SUCCESS 0

# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>

# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_idx;
	int				eat_count;
	size_t			death_time;
	size_t			eating_time;
	size_t			sleeping_time;
	size_t			last_start_eating_time;
	size_t			time_stamp;
	size_t			current_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				death_time;
	int				eating_time;
	int				sleeping_time;
	int				must_eat_num;
	size_t			start_time;
	int				each_philo_eat_count[200];
	int				continue_or_end;
	int				count_eaten_philo;
	struct s_philo	philo[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	gp_mutex;
	pthread_mutex_t	put_action;
	pthread_t		philo_tid[200];
	pthread_t		monitor_tid;
}	t_data;

/*libft_philo*/
int		ato_positive_int(const char *str);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

/*one_philosopher*/
void	*simulate_one_philosopher(void *arg);
int		think(t_data *data, t_philo *philo, size_t i);
int		take_forks_and_eat(t_data *data, t_philo *philo);
int		sleep_philo(t_data *data, t_philo *philo);
int		update_time_stamp(t_data *data, t_philo *philo);
size_t	get_mili_sec(void);
void	put_action(t_data *data, t_philo *philo, int action_num);
int		put_action_and_usleep(t_philo *philo, t_data *data, \
								int action_num, size_t specified_sec);

/*src*/
int		put_error(char *error_message, char *str);
void	pthread_create_and_join(t_data *data);
int		init_data(t_data *data);
void	*monitor(void *arg);
void	case_of_a_philo(t_data *data);

#endif
