/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:57:43 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/31 13:27:47 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	put_error(char *error_message, char *str)
{
	if (error_message)
		ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (ERROR);
}
