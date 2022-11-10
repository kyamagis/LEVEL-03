/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_to_double_pointer.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:24:18 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/18 23:19:00 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/make_absolute_path.h"

size_t	count_envp(t_env *envp_list)
{
	size_t	i;

	i = 0;
	while (envp_list)
	{
		envp_list = envp_list->next;
		i++;
	}
	return (i);
}

char	**envp_list_to_double_pointer(t_env *envp_list, \
										char **cmd_option)
{
	char	**envp;
	size_t	i;
	char	*name_equal;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * \
						(count_envp(envp_list) + 1));
	if (envp == NULL)
		ft_exit(MALLOC_FAILURE);
	envp[0] = NULL;
	i = 0;
	while (envp_list)
	{
		name_equal = my_strjoin(envp_list->env_name, "=");
		envp[i] = my_strjoin(name_equal, envp_list->env_content);
		envp_list = envp_list->next;
		free(name_equal);
		i++;
	}
	if (envp[0] == NULL)
		strerror_exit(ENOENT, cmd_option[0], 127);
	envp[i] = NULL;
	return (envp);
}

/* 
static t_env	*malloc_envp_list(char *envp)
{
	size_t		equal_idx;
	t_env	*envp_list;

	envp_list = (t_env *)malloc(sizeof(t_env));
	if (envp_list == NULL)
		ft_exit(MALLOC_FAILURE);
	equal_idx = ft_strstr_idx(envp, "=");
	envp_list->env_name = ft_substr(envp, 0, equal_idx);
	envp_list->env_content = \
	ft_substr(envp + equal_idx + 1, 0, ft_strlen(envp));
	envp_list->next = NULL;
	return (envp_list);
}



t_env	*make_envp_list(char **envp)
{
	t_env	*envp_list;
	t_env	*tmp;
	size_t		i;

	i = 1;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	envp_list = malloc_envp_list(envp[0]);
	tmp = envp_list;
	while (envp[i])
	{
		tmp->next = malloc_envp_list(envp[i]);
		tmp = tmp->next;
		i++;
	}
	return (envp_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envp_list = make_envp_list(envp);
	envp_list_to_double_pointer(envp_list, \
										NULL);
} */