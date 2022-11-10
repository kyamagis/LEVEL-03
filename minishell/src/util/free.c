/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:07:58 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/19 21:35:49 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_malloc(char **malloc)
{
	size_t	i;

	i = 0;
	while (malloc[i])
	{
		free(malloc[i]);
		malloc[i++] = NULL;
	}
	free(malloc);
	malloc = NULL;
}

void	free_cmd_and_struct_exit(char *cmd, t_shell *s)
{
	t_env	*tmp;

	free(cmd);
	while (s->envp_list)
	{
		tmp = s->envp_list->next;
		free(s->envp_list->env_content);
		free(s->envp_list->env_name);
		free(s->envp_list);
		s->envp_list = tmp;
	}
	status_on_and_exit(s);
}

void	free_tmp_cmds(char *cmd, t_shell *s)
{
	free(s->tmp_rd_cmd);
	free(s->tmp_rd_cmd_flag);
	free_cmd_and_struct_exit(cmd, s);
}

void	free_total_malloc_and_exit(char *cmd, t_shell *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s->tmp_rd_cmd[i])
	{
		j = 0;
		while (s->tmp_rd_cmd[i][j])
			free(s->tmp_rd_cmd[i][j++]);
		free(s->tmp_rd_cmd[i]);
		free(s->tmp_rd_cmd_flag[i++]);
	}
	if (s->tmp_arr)
	{
		i = 0;
		while (s->tmp_arr[i])
			free(s->tmp_arr[i++]);
		free(s->tmp_arr);
	}
	free_tmp_cmds(cmd, s);
}

void	free_tmp_malloc(t_shell *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s->tmp_rd_cmd[i])
	{
		j = 0;
		while (s->tmp_rd_cmd[i][j])
			free(s->tmp_rd_cmd[i][j++]);
		free(s->tmp_rd_cmd[i]);
		free(s->tmp_rd_cmd_flag[i]);
		i++;
	}
	free(s->tmp_rd_cmd);
	free(s->tmp_rd_cmd_flag);
}
