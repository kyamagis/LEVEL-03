/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:25:15 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 19:41:17 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "exe_cmd.h"

typedef struct s_shell_common_data
{
	size_t					here_doc_count;
	size_t					pipe_count;
	char					***tmp_rd_cmd;
	char					**tmp_arr;
	size_t					**tmp_rd_cmd_flag;
	struct s_file_name_list	*file_name_list;
	struct s_cmd_line_list	*cmd;
	struct s_envp_list		*envp_list;
}					t_shell;

typedef struct s_envp_list
{
	char				*env_name;
	char				*env_content;
	int					plus_flg;
	struct s_envp_list	*next;
}					t_env;

typedef struct s_cmd_line_list
{
	char					**cmd_option;
	char					**redirections;
	size_t					*quote_flg;
	int						output_redirection;
	pid_t					pid;
	struct s_cmd_line_list	*next;
}	t_cmd;

typedef struct s_file_name_list
{
	char					*file_name;
	struct s_file_name_list	*next;
}	t_file_name_list;

#endif