/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:32:24 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 19:43:22 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "exe_cmd.h"

/*here_document*/
int					here_document(t_shell *shell, \
						char *end_str, \
						size_t quote_flg, \
						int *pipefd);
t_file_name_list	*find_list_tail(t_shell *shell);
char				*create_unique_file_name(char *file_name);
void				put_env(char *str, \
								t_env *envp_list, int infile_fd);
/*redirections*/
int					stdin_redirect(char *infile_name, int *pipefd);
int					over_write_redirection(char *outfile_name, int *pipefd);
int					add_write_redirection(char *outfile_name, \
											int *pipefdoutfile_name);
int					detect_redirection(t_shell *shell, \
								t_cmd	*cmd_line_list, \
								int *pipefd);
int					discriminate_accessible_infile(char *infile_name);
int					discriminate_accessible_outfile(char *outfile_name);

#endif