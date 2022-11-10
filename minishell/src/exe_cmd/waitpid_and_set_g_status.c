/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid_and_set_g_status.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:15:07 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/24 18:10:09 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exe_cmd.h"

void	waitpid_and_set_g_status(t_shell *shell)
{
	int		wstatus;
	t_cmd	*cmd_line_list;
	size_t	i;

	cmd_line_list = shell->cmd;
	i = 0;
	while (i <= shell->pipe_count && cmd_line_list->pid)
	{
		if (waitpid(cmd_line_list->pid, &wstatus, 0) == -1)
			g_status = FAILURE;
		cmd_line_list = cmd_line_list->next;
		i++;
	}
	if (g_status == 1000)
		g_status = 1;
	else if (g_status != 1 && WIFSIGNALED(wstatus))
		g_status = WTERMSIG(wstatus) + 128;
	else if (WIFEXITED(wstatus))
		g_status = WEXITSTATUS(wstatus);
	delete_created_all_file(shell);
}
