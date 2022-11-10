/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:27:55 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:36:16 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMD_H
# define EXE_CMD_H

# define OPEN_FAILURE "open failure"
# define WAITPID_FAILURE "Waitpid failure"
# define MALLOC_FAILURE "Malloc failure"
# define PIPE_FAILURE "Pipe failure"
# define FORK_FAILURE "Fork failure"
# define EXECVE_FAILURE "Execve failure"
# define UNLIMK_FAILURE "Unlink failure"
# define USAGE "usage   : ./minishell infile \"cmd1\" \"cmd2\" outfile\n\
example : ./minishell infile \"ls -l\" \"wc -l\" outfile\n\
        : ./minishell infile \"cat -n\" \"cat\" outfile\n\
	: ./minishell here_doc END \"cat -n\" \"cat\" outfile"
# define COMMAND_NOT_FOUND "Command not found"
# define DUP2_ERROR "dup2 error"
# define ONLY_WRITE_PERMISSION 0644
# define READ 0
# define WRITE 1
# define CHILD_PROCESS 0
# define REDIRECTON 0
# define ACCESSIBLE 0
# define NOT_ACCESS -1
# define FOUND 0
# define NOT_FOUND 1
# define INFILE 1
# define FIRST_FORK 0
# define SECOUND_FORK 1
# define SUCCESS 0
# define FAILURE 1

// # include <readline/readline.h>
// # include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "struct.h"
# include "minishell.h"
# include "gnl.h"
# include "lib_shell.h"
# include "redirections.h"
# include "builtin.h"
# include "make_absolute_path.h"
# include "exe_cmd_utils.h"

//int	g_status;

void	waitpid_and_set_g_status(t_shell *shell);
void	not_pipe_and_builtin_cmd(t_shell *shell);
void	multiple_pipe(t_shell *shell);
void	exe_cmd(t_shell *shell);

#endif
