/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list_tail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:19:43 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:43:57 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/redirections.h"

static t_file_name_list	*malloc_file_name_list(void)
{
	t_file_name_list	*file_name_list;

	file_name_list = (t_file_name_list *)malloc(sizeof(t_file_name_list));
	if (file_name_list == NULL)
		ft_exit(MALLOC_FAILURE);
	file_name_list->file_name = NULL;
	file_name_list->next = NULL;
	return (file_name_list);
}

t_file_name_list	*find_list_tail(t_shell *shell)
{
	t_file_name_list	*tmp;

	if (shell->file_name_list == NULL)
	{
		shell->file_name_list = malloc_file_name_list();
		return (shell->file_name_list);
	}
	tmp = shell->file_name_list;
	while (tmp->next)
		tmp = tmp->next;
	if (shell->here_doc_count == 1)
	{	
		tmp->next = malloc_file_name_list();
		tmp = tmp->next;
	}
	return (tmp);
}
