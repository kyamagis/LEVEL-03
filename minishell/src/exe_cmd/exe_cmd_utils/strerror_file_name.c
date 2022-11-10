/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerror_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:35:12 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:45:39 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

int	strerror_file_name(int error_plus_flg, char *file_name, int status)
{
	g_status = status;
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error_plus_flg), STDERR_FILENO);
	return (-1);
}
