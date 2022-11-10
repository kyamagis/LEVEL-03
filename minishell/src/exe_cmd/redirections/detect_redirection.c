/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:26:01 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:43:11 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/redirections.h"

static int	detect_input_redirection(t_shell *shell, \
									t_cmd	*cmd_line_list, \
									int *pipefd, \
									size_t	i)
{
	int		failure_flg;
	char	**redirections;

	redirections = cmd_line_list->redirections;
	failure_flg = 0;
	if (ft_strncmp(redirections[i], "<<", 2) == FOUND)
		failure_flg = here_document(shell, \
									&redirections[i][2], \
									cmd_line_list->quote_flg[i], \
									pipefd);
	else if (ft_strncmp(redirections[i], "<", 1) == FOUND)
		failure_flg = stdin_redirect(&redirections[i][1], pipefd);
	return (failure_flg);
}

static int	detect_output_redirection(t_cmd *cmd_line_list, \
									int *pipefd, \
									size_t	i)
{
	int		failure_flg;
	char	**redirections;

	redirections = cmd_line_list->redirections;
	failure_flg = 0;
	if (ft_strncmp(redirections[i], ">>", 2) == FOUND)
		failure_flg = add_write_redirection(&redirections[i][2], pipefd);
	else if (ft_strncmp(redirections[i], ">", 1) == FOUND)
		failure_flg = over_write_redirection(&redirections[i][1], pipefd);
	if (failure_flg == 1)
		cmd_line_list->output_redirection = FOUND;
	return (failure_flg);
}

static int	scan_redirection(t_shell *shell, \
							t_cmd	*cmd_line_list, \
							int *pipefd)
{
	size_t	i;
	int		failure_flg;

	failure_flg = 0;
	i = 0;
	while (cmd_line_list->redirections[i])
	{
		if (ft_strncmp(cmd_line_list->redirections[i], "<", 1) == FOUND)
			failure_flg = detect_input_redirection(shell, \
												cmd_line_list, \
												pipefd, \
												i);
		else if (ft_strncmp(cmd_line_list->redirections[i], ">", 1) == FOUND)
			failure_flg = detect_output_redirection(cmd_line_list, pipefd, i);
		if (failure_flg == -1)
			return (-1);
		i++;
	}
	return (failure_flg);
}

int	detect_redirection(t_shell *shell, \
						t_cmd	*cmd_line_list, \
						int *pipefd)
{
	if (cmd_line_list->redirections == NULL)
		return (0);
	shell->here_doc_count = 0;
	return (scan_redirection(shell, cmd_line_list, pipefd));
}
