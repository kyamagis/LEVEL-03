/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:11:41 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/22 20:56:19 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exe_cmd.h"

static void	dup2_pipefd_std(t_cmd	*cmd_line_list, \
							int *pipefd, \
							int prev_pipefd_read)
{
	if (cmd_line_list == NULL)
		return ;
	if (0 < prev_pipefd_read)
	{
		if (dup2(prev_pipefd_read, STDIN_FILENO) == -1)
			ft_exit(DUP2_ERROR);
		close(prev_pipefd_read);
	}
	if (cmd_line_list->next || \
		cmd_line_list->output_redirection == FOUND)
	{
		close(pipefd[READ]);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
			ft_exit(DUP2_ERROR);
		close(pipefd[WRITE]);
	}
}

static void	execute_cmd(t_shell *shell, \
					t_cmd	*cmd_line_list, \
					int *pipefd, \
					int prev_pipefd_read)
{
	dup2_pipefd_std(cmd_line_list, pipefd, prev_pipefd_read);
	if (!cmd_line_list || !cmd_line_list->cmd_option || \
		!cmd_line_list->cmd_option[0] || !cmd_line_list->cmd_option[0][0])
		exit(EXIT_SUCCESS);
	if (isbuiltin_cmd(cmd_line_list) == FOUND)
	{
		exe_a_builtin_cmd(shell, cmd_line_list);
		exit(g_status);
	}
	make_absolute_path(shell, cmd_line_list->cmd_option);
}

static int	update_pipefd_for_redirection(t_shell *shell, \
										t_cmd	*cmd_line_list, \
										int *pipefd, \
										int *prev_pipefd_read)
{
	int	tmp_pipefd[2];

	tmp_pipefd[READ] = STDIN_FILENO;
	tmp_pipefd[WRITE] = STDOUT_FILENO;
	if (detect_redirection(shell, \
							cmd_line_list, \
							tmp_pipefd) == -1)
		return (-1);
	if (tmp_pipefd[READ] != STDIN_FILENO)
	{	
		if (*prev_pipefd_read != STDIN_FILENO)
			close(*prev_pipefd_read);
		*prev_pipefd_read = tmp_pipefd[READ];
	}
	if (tmp_pipefd[WRITE] != STDOUT_FILENO)
	{
		close(pipefd[WRITE]);
		pipefd[WRITE] = tmp_pipefd[WRITE];
	}
	return (SUCCESS);
}

static int	fork_and_execution(t_shell *shell, \
							t_cmd	*cmd_line_list, \
							int *pipefd, \
							int *prev_pipefd_read)
{
	if (pipe(pipefd) == -1)
		ft_exit(PIPE_FAILURE);
	if (update_pipefd_for_redirection(shell, \
		cmd_line_list, pipefd, prev_pipefd_read) == -1)
		return (-1);
	signal(SIGQUIT, sigfunc2);
	cmd_line_list->pid = fork();
	if (cmd_line_list->pid == -1)
		ft_exit(FORK_FAILURE);
	else if (cmd_line_list->pid == CHILD_PROCESS)
		execute_cmd(\
		shell, cmd_line_list, pipefd, *prev_pipefd_read);
	close(pipefd[WRITE]);
	if (2 < *prev_pipefd_read)
		close(*prev_pipefd_read);
	*prev_pipefd_read = pipefd[READ];
	return (SUCCESS);
}

void	multiple_pipe(t_shell *shell)
{
	size_t	i;
	t_cmd	*cmd_line_list;
	int		prev_pipefd_read;
	int		pipefd[2];

	cmd_line_list = shell->cmd;
	prev_pipefd_read = STDIN_FILENO;
	i = 0;
	while (i <= shell->pipe_count)
	{
		cmd_line_list->output_redirection = NOT_FOUND;
		if (fork_and_execution(shell, \
			cmd_line_list, pipefd, &prev_pipefd_read) == -1)
		{
			if (pipefd[WRITE] != STDOUT_FILENO)
				close(pipefd[WRITE]);
			break ;
		}
		cmd_line_list = cmd_line_list->next;
		i++;
	}
	if (prev_pipefd_read != STDIN_FILENO)
		close(prev_pipefd_read);
	waitpid_and_set_g_status(shell);
	signal(SIGQUIT, SIG_IGN);
}
