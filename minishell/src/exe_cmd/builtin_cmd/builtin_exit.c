/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:19:09 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:45:47 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

static uint8_t	error_message(char *str, int *not_numeric_char)
{
	*not_numeric_char = FOUND;
	ft_putstr_fd("exit: ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
	return (255);
}

static uint8_t	ft_dis_max_min(unsigned long num, \
									int flag, char *str, \
									int *not_numeric_char)
{
	if (num == 0)
		return (0);
	if ((flag == 1 && LONG_MAX < num) || \
		(flag == -1 && LONG_MAX < num - 1))
		return (error_message(str, not_numeric_char));
	*not_numeric_char = NOT_FOUND;
	return ((uint8_t)(num * flag));
}

static uint8_t	a_to_int8(char *str, \
							int flag, size_t i, \
							int *not_numeric_char)
{
	unsigned long	num;
	size_t			digcount;

	num = 0;
	digcount = 1;
	while (ft_isdigit(str[i]))
	{
		if (num != 0)
			digcount++;
		if (19 < digcount)
			return (error_message(str, not_numeric_char));
		num = 10 * num + (str[i] - '0');
		i++;
	}
	if (!ft_isdigit(str[i]) && str[i] != '\0')
		return (error_message(str, not_numeric_char));
	return (ft_dis_max_min(num, flag, str, not_numeric_char));
}

static uint8_t	ft_a_to_int8(char *str, int *not_numeric_char)
{
	size_t			i;
	int				flag;

	flag = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			flag = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (error_message(str, not_numeric_char));
	return (a_to_int8(str, flag, i, not_numeric_char));
}

void	builtin_exit(char **cmd_option)
{
	int	status;
	int	not_numeric_char;

	not_numeric_char = FOUND;
	status = EXIT_SUCCESS;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd_option[1] == NULL)
		status = EXIT_SUCCESS;
	else if (cmd_option[2] == NULL)
		status = (int)ft_a_to_int8(cmd_option[1], &not_numeric_char);
	else
	{
		status = (int)ft_a_to_int8(cmd_option[1], &not_numeric_char);
		if (not_numeric_char == NOT_FOUND)
		{
			ft_putendl_fd("exit: too many arguments", STDOUT_FILENO);
			g_status = EXIT_FAILURE;
			return ;
		}
	}
	g_status = status;
	exit(status);
}
