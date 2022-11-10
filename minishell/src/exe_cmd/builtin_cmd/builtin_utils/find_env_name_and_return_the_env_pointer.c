/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_name_and_return_the_env_pointer.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:30:34 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:17 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/builtin.h"

t_env	*find_env_name_and_return_the_env_pointer(\
		char *env_name, t_shell *shell)
{
	t_env	*envp_list;

	envp_list = shell->envp_list;
	while (envp_list)
	{
		if (ft_strcmp(env_name, envp_list->env_name) == FOUND)
			return (envp_list);
		envp_list = envp_list->next;
	}
	return (NULL);
}
