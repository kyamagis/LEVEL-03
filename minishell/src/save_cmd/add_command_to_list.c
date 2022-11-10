/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:53:01 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/19 21:53:01 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_exit(char **cmds, t_shell *s)
{
	free_malloc(cmds);
	free_total_malloc_and_exit(NULL, s);
}

static t_cmd	*new_cmd_node(t_shell *s, size_t i, char **cmd_arr, char **cmds)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
	{
		free_malloc(cmd_arr);
		free_exit(cmds, s);
	}
	node->cmd_option = cmd_arr;
	node->redirections = s->tmp_rd_cmd[i];
	node->quote_flg = s->tmp_rd_cmd_flag[i];
	node->next = NULL;
	return (node);
}

static char	**make_first_node(char **cmds, t_shell *s)
{
	char	**cmd_arr;

	if (cmds[0][0] == '\0')
		return (make_null_arr(NULL, s));
	cmd_arr = split_for_add_list(cmds[0], ' ');
	if (!cmd_arr)
		free_exit(cmds, s);
	return (cmd_arr);
}

void	add_command_to_list(char **cmds, t_shell *s)
{
	char	**cmd_arr;
	size_t	i;
	t_cmd	*tmp;

	cmd_arr = make_first_node(cmds, s);
	i = 0;
	s->cmd = new_cmd_node(s, i, cmd_arr, cmds);
	tmp = s->cmd;
	i++;
	while (cmds[i])
	{
		if (cmds[i][0] == '\0')
			cmd_arr = make_null_arr(NULL, s);
		else
		{
			cmd_arr = split_for_add_list(cmds[i], ' ');
			if (!cmd_arr)
				free_exit(cmds, s);
		}
		tmp->next = new_cmd_node(s, i, cmd_arr, cmds);
		tmp = tmp->next;
		i++;
	}
	free_malloc(cmds);
}
