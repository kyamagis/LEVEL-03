/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_write_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:09:07 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:43:17 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/redirections.h"

int	over_write_redirection(char *outfile_name, int *pipefd)
{
	int	outfile_fd;

	if (discriminate_accessible_outfile(outfile_name) == -1)
		return (-1);
	outfile_fd = open(outfile_name, \
						O_CREAT | O_WRONLY | O_TRUNC, ONLY_WRITE_PERMISSION);
	if (outfile_fd == -1)
		ft_exit(OPEN_FAILURE);
	if (pipefd[WRITE] != STDOUT_FILENO)
		close(pipefd[WRITE]);
	pipefd[WRITE] = outfile_fd;
	return (1);
}
