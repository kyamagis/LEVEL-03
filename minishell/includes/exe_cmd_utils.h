/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:08:58 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:02:09 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMD_UTILS_H
# define EXE_CMD_UTILS_H

# include "exe_cmd.h"

/*exe_cmd_utils*/
void	ft_exit(char *error_plus_flg);
void	message_exit(char *message, char *command, int exit_status);
void	strerror_exit(int error_plus_flg, char *file_name, int exit_status);
void	delete_created_all_file(t_shell	*shell);
void	delete_created_a_file(t_file_name_list *file_name_list);
int		isbuiltin_cmd(t_cmd *cmd_line_list);
int		strerror_file_name(int error_plus_flg, char *file_name, int status);
void	exe_a_builtin_cmd(t_shell *shell, t_cmd *cmd_line_list);

#endif