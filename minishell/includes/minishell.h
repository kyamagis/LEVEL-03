/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:42:16 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/25 20:14:37 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdbool.h>
# include <signal.h>
# include "exe_cmd.h"

# define STDERR 2

# define ERR1	"ERR: Do not include a space after [\"]"

extern size_t	g_status;

t_env		*new_node(char *cmd);
char		*replace_env_to_command(char *cmd, t_shell *s);
char		*search_env_and_replace(char *search_str, t_shell *s, char *cmd);
size_t		skip_inside_single_quote(char *cmd, size_t *index);
char		**split_for_parser(char *cmd, t_shell *s);
bool		validity_of_env_after_escape(char *cmd);
t_cmd		*new_s_cmd_node(t_shell *s);
void		add_command_to_list(char **cmds, t_shell *s);
void		quote_check(char *cmd, t_shell *s);
void		save_redirect(char *cmd_line, t_shell *s);
char		**make_rd_arr(char *cmd, char **rd_str, char *cmds, t_shell *s);
char		**rm_quote_from_rd_str(char **rd_arr, char *cmd_line, t_shell *s);
char		*make_new_cmd_without_redirect(char *cmd_line, t_shell *s);
char		*rm_space(char *cmd, t_shell *s);
size_t		skip_inside_double_quote(char *cmd, size_t	*index);
char		**split_with_valid_pipe(char *cmd, t_shell *s);
void		importing_main_shell_env(char **envp, t_shell *s);
char		*make_null_str(char *cmd, t_shell *s);
void		signal_set(void);
void		sigfunc(int signum);
void		sigfunc_quit_program(int signum);
void		free_cmd_and_struct_exit(char *cmd, t_shell *s);
t_shell		*init(int argc, char **argv, char **envp);
void		status_on_and_exit(t_shell *s);
void		free_tmp_cmds(char *cmd, t_shell *s);
void		free_exit_for_save_redirect(char *cmd_line, t_shell *s);
void		free_malloc(char **malloc);
char		*add_final_char_str(void);
void		free_total_malloc_and_exit(char *cmd, t_shell *s);
char		*syntax_check(char *cmd, t_shell *s);
void		free_tmp_malloc(t_shell *s);
void		put_error(char *err_str, char *cmd, t_shell *s);
char		**make_null_arr(char *cmd, t_shell *s);
size_t		skip_quote(char *cmd, size_t	*index);
bool		mini_strstr(char *str1, char *str2);
char		**replace_env(char **cmd_arr, t_shell *s);
char		*no_env_in_list(char *cmd, char *search_str);
void		syntax_check2(char *cmd, t_shell *s);
void		check_syntax3(char *cmd, t_shell *s);
void		check_malloc_error(char *str, char **split, char *cmd, t_shell *s);
void		rm_quote(t_shell *s);
void		add_inside_quote(char *old, char *new, size_t *i, size_t *j);
size_t		skip_quote_finish_second_quote(char *cmd, size_t	*index);
char		**split_for_add_list(char *s, char c);
int			check_first_is_quote(char c);
void		case_of_no_delimiter(char *s, int *index, size_t *i, char c);
void		free_cmd_and_struct_exit_0(char *cmd, t_shell *s);
void		sigfunc2(int signum);
char		**check_new_line(char *cmd_line, t_shell *s);
void		sig_heredoc_ctrl_c(int signum);
size_t		skip_inside_single_quote_2(char *cmd, size_t *index);
void		double_quote_check(char *cmd, size_t index, bool *flag);
void		count_m_size_u(char *cmd, char *search_str, size_t *i, bool *flag);
bool		check_str_match(char *str, size_t index, char *search_str);
char		*make_search_str(char *cmd, size_t search_str_size);

#endif