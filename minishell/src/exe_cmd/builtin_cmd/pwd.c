/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:52:35 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:01 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

void	pwd(void)
{
	char	*absolute_path;

	absolute_path = getcwd(NULL, 0);
	if (absolute_path == NULL)
	{
		g_status = FAILURE;
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	ft_putendl_fd(absolute_path, STDOUT_FILENO);
	g_status = SUCCESS;
	free(absolute_path);
}

/*
int	main(void)
{
    pwd();
}
*/