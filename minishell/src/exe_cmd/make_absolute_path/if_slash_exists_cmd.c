/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_slash_exists_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:30:24 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:44:43 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/make_absolute_path.h"

void	if_slash_exists_cmd(char **envp, char **cmd_and_options)
{
	int	fd;

	if (ft_strchr(cmd_and_options[0], '/') == NULL)
		return ;
	fd = open(cmd_and_options[0], O_DIRECTORY);
	close(fd);
	if (fd != -1)
		strerror_exit(EISDIR, cmd_and_options[0], 126);
	if (access(cmd_and_options[0], X_OK) == ACCESSIBLE)
	{	
		execve(cmd_and_options[0], cmd_and_options, envp);
		ft_exit(EXECVE_FAILURE);
	}
	else if (access(cmd_and_options[0], F_OK) == ACCESSIBLE)
		strerror_exit(EACCES, cmd_and_options[0], 126);
	else
		strerror_exit(ENOENT, cmd_and_options[0], 127);
}
