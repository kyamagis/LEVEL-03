/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_envp_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:24:18 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/20 11:34:18 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/make_absolute_path.h"

char	*path_envp_to_str(t_shell *shell, char **cmd_option)
{
	t_env	*path_env;

	path_env = find_env_name_and_return_the_env_pointer("PATH", shell);
	if (path_env == NULL || path_env->env_content == NULL || \
		path_env->env_content[0] == '\0')
		strerror_exit(ENOENT, cmd_option[0], 127);
	return (ft_strdup(path_env->env_content));
}
