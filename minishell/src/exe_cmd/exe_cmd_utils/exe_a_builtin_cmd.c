/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_a_builtin_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:57:53 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/17 11:47:01 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

void	exe_a_builtin_cmd(t_shell *shell, \
							t_cmd *cmd_line_list)
{
	if (ft_strcmp(cmd_line_list->cmd_option[0], "echo") == FOUND)
		echo(cmd_line_list->cmd_option);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "cd") == FOUND)
		cd(cmd_line_list->cmd_option, shell);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "pwd") == FOUND)
		pwd();
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "export") == FOUND)
		builtin_export(shell, cmd_line_list->cmd_option);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "unset") == FOUND)
		unset(cmd_line_list->cmd_option, shell);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "env") == FOUND)
		env(cmd_line_list->cmd_option, shell->envp_list);
	else if (ft_strcmp(cmd_line_list->cmd_option[0], "exit") == FOUND)
		builtin_exit(cmd_line_list->cmd_option);
}
