/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:56:31 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/17 12:05:59 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

int	isbuiltin_cmd(t_cmd *cmd_line_list)
{
	if (cmd_line_list == NULL || cmd_line_list->cmd_option == NULL || \
		cmd_line_list->cmd_option[0] == NULL)
		return (NOT_FOUND);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "echo") == FOUND)
		return (FOUND);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "cd") == FOUND)
		return (FOUND);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "pwd") == FOUND)
		return (FOUND);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "export") == FOUND)
		return (FOUND);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "unset") == FOUND)
		return (FOUND);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "env") == FOUND)
		return (FOUND);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "exit") == FOUND)
		return (FOUND);
	return (NOT_FOUND);
}
