/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_puterror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:48:59 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:11 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/builtin.h"

void	builtin_puterror(char *builtin_cmd, char *str)
{
	ft_putstr_fd(builtin_cmd, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	g_status = FAILURE;
}
