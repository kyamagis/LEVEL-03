/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:09:14 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:43:19 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/redirections.h"

int	stdin_redirect(char *infile_name, int *pipefd)
{
	int	infile_fd;

	if (discriminate_accessible_infile(infile_name) == -1)
		return (-1);
	infile_fd = open(infile_name, O_RDONLY);
	if (infile_fd == -1)
		ft_exit(OPEN_FAILURE);
	if (pipefd[READ] != STDIN_FILENO)
		close(pipefd[READ]);
	pipefd[READ] = infile_fd;
	return (1);
}
