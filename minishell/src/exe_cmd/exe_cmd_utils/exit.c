/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:08:47 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/19 19:57:10 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

void	bash_strerror_exit(int error_plus_flg, \
				char *file_name1, char *file_name2)
{
	ft_putstr_fd(file_name1, STDERR_FILENO);
	write(STDERR_FILENO, ": ", STDERR_FILENO);
	ft_putstr_fd(file_name2, STDERR_FILENO);
	write(STDERR_FILENO, ": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error_plus_flg), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	message_exit(char *message, char *command, int exit_status)
{
	ft_putstr_fd(command, STDERR_FILENO);
	write(STDERR_FILENO, ": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	exit(exit_status);
}

void	ft_exit(char *error_plus_flg)
{
	ft_putendl_fd(error_plus_flg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	strerror_exit(int error_plus_flg, char *file_name, int exit_status)
{
	ft_putstr_fd(file_name, STDERR_FILENO);
	write(STDERR_FILENO, ": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error_plus_flg), STDERR_FILENO);
	exit(exit_status);
}
