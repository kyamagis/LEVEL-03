/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_pipe_and_builtin_cmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:47:12 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:42:22 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exe_cmd.h"

static int	dup_std_fd(int *tmp_std_fd)
{
	tmp_std_fd[READ] = dup(STDIN_FILENO);
	if (tmp_std_fd[READ] == -1)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		g_status = FAILURE;
		return (-1);
	}
	tmp_std_fd[WRITE] = dup(STDOUT_FILENO);
	if (tmp_std_fd[WRITE] == -1)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		g_status = FAILURE;
		return (-1);
	}
	return (1);
}

static void	pipefd_init(int *pipefd)
{
	pipefd[READ] = STDIN_FILENO;
	pipefd[WRITE] = STDOUT_FILENO;
}

static int	dup2_fd_stdfd(int *fd)
{
	if (fd[READ] != STDIN_FILENO)
	{
		if (dup2(fd[READ], STDIN_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			g_status = FAILURE;
			ft_exit(DUP2_ERROR);
			return (-1);
		}
		close(fd[READ]);
	}
	if (fd[WRITE] != STDOUT_FILENO)
	{
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			g_status = FAILURE;
			ft_exit(DUP2_ERROR);
			return (-1);
		}
		close(fd[WRITE]);
	}
	return (1);
}

void	not_pipe_and_builtin_cmd(t_shell *shell)
{
	int	tmp_std_fd[2];
	int	pipefd[2];

	if (dup_std_fd(tmp_std_fd) == -1)
		return ;
	pipefd_init(pipefd);
	if (detect_redirection(shell, \
							shell->cmd, \
							pipefd) == -1)
		return ;
	dup2_fd_stdfd(pipefd);
	exe_a_builtin_cmd(shell, shell->cmd);
	dup2_fd_stdfd(tmp_std_fd);
	delete_created_all_file(shell);
}
