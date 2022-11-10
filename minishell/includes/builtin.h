/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:41:16 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/17 11:46:41 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "exe_cmd.h"

/*builtin*/
void		echo(char **echo_cmd_option);
void		env(char **cmd_option, t_env *envp_list);
void		pwd(void);
void		builtin_exit(char **cmd_option);
void		unset(char **cmd_option, t_shell *shell);
void		cd(char **cmd_option, t_shell *shell);

/*builtin_utils*/
int			isalnum_underscore(int c);
int			isalnum_underscore_str(char *str);
void		builtin_puterror(char *builtin_cmd, char *str);
t_env		*find_env_name_and_return_the_env_pointer(char *env_name, \
														t_shell *shell);

/*export*/
void		builtin_export(t_shell *shell, char **export_cmd_line);
t_env		*make_export_list(char **export_cmd_line);
void		add_export_cmd_line_to_envp(t_shell *shell, \
											char **export_cmd_line);
void		bash_strerror_exit(int error_plus_flg, char *file_name1, \
								char *file_name2);

#endif