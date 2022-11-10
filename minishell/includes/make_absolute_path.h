/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_absolute_path.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:45:29 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/20 11:18:04 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_ABSOLUTE_PATH_H
# define MAKE_ABSOLUTE_PATH_H

# include "exe_cmd.h"

/*make_absolute_path*/
char	**envp_list_to_double_pointer(t_env *envp_list, \
										char **cmd_option);
char	*path_envp_to_str(t_shell *shell, char **cmd_option);
void	if_slash_exists_cmd(char **envp, char **cmd_and_options);
void	make_absolute_path(t_shell *shell, char **cmd_option);

#endif