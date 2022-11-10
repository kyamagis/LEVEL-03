/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export_cmdline_to_envp.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:31:42 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:29 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/builtin.h"

static void	envp_env_content_join_or_overwrite(\
			t_env	*export_tmp, t_env *envp_tmp)
{
	char	*tmp_str;

	if (export_tmp->plus_flg == 1)
	{
		tmp_str = my_strjoin(envp_tmp->env_content, export_tmp->env_content);
		free(envp_tmp->env_content);
		envp_tmp->env_content = tmp_str;
	}
	else
	{	
		if (export_tmp->env_content == NULL)
			return ;
		free(envp_tmp->env_content);
		envp_tmp->env_content = my_strdup(export_tmp->env_content);
	}
}

static void	add_envp_back(t_env *export_tmp, \
							t_env *envp_tmp, \
							t_shell *shell)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == NULL)
	{
		g_status = 1;
		exit(EXIT_FAILURE);
	}
	tmp->env_name = my_strdup(export_tmp->env_name);
	tmp->env_content = my_strdup(export_tmp->env_content);
	tmp->next = NULL;
	if (shell->envp_list == NULL)
		shell->envp_list = tmp;
	else
		envp_tmp->next = tmp;
}

static void	free_export_list(t_env *export_list)
{
	t_env	*tmp;

	while (export_list)
	{
		free(export_list->env_name);
		free(export_list->env_content);
		tmp = export_list;
		export_list = export_list->next;
		free(tmp);
	}
}

static void	add_join_or_overwrit_envp(\
			t_env *export_tmp, t_shell *shell)
{
	t_env	*envp_tmp;
	t_env	*envp_tail;

	envp_tmp = shell->envp_list;
	envp_tail = shell->envp_list;
	while (envp_tmp)
	{
		if (ft_strcmp(export_tmp->env_name, envp_tmp->env_name) == FOUND)
		{	
			envp_env_content_join_or_overwrite(export_tmp, envp_tmp);
			return ;
		}
		if (envp_tmp->next == NULL)
			envp_tail = envp_tmp;
		envp_tmp = envp_tmp->next;
	}
	if (envp_tmp == NULL)
		add_envp_back(export_tmp, envp_tail, shell);
}

void	add_export_cmd_line_to_envp(\
			t_shell *shell, char **export_cmd_line)
{
	t_env	*export_list;
	t_env	*export_tmp;

	export_list = make_export_list(export_cmd_line);
	export_tmp = export_list;
	while (export_tmp)
	{
		add_join_or_overwrit_envp(export_tmp, shell);
		export_tmp = export_tmp->next;
	}
	free_export_list(export_list);
}
