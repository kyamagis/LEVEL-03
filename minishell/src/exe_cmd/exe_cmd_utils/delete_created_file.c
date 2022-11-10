/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_created_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:13:45 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:45:22 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

void	delete_created_all_file(t_shell *shell)
{
	t_file_name_list	*file_name_list;
	t_file_name_list	*tmp;

	if (shell->file_name_list == NULL)
		return ;
	file_name_list = shell->file_name_list;
	while (file_name_list)
	{
		if (unlink(file_name_list->file_name) == -1)
			ft_exit(UNLIMK_FAILURE);
		free(file_name_list->file_name);
		tmp = file_name_list;
		file_name_list = file_name_list->next;
		free(tmp);
	}
	shell->file_name_list = NULL;
}

void	delete_created_a_file(t_file_name_list *file_name_list)
{
	if (file_name_list == NULL)
		return ;
	if (unlink(file_name_list->file_name) == -1)
		ft_exit(UNLIMK_FAILURE);
	free(file_name_list->file_name);
	file_name_list->file_name = NULL;
}
