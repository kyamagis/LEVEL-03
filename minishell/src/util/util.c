/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:09:50 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/17 19:21:10 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	skip_inside_double_quote(char *cmd, size_t	*index)
{
	size_t	i;

	i = (*index);
	(*index)++;
	while (cmd[*index] != '\"')
		(*index)++;
	(*index)++;
	i = (*index) - i;
	return (i);
}

char	*make_null_str(char *cmd, t_shell *s)
{
	char	*null_str;

	null_str = (char *)malloc(sizeof(char) * 1);
	if (!null_str)
		free_total_malloc_and_exit(cmd, s);
	null_str[0] = '\0';
	return (null_str);
}

char	**make_null_arr(char *cmd, t_shell *s)
{
	char	**cmd_arr;

	cmd_arr = (char **)malloc(sizeof(char *) * 2);
	if (!cmd_arr)
		free_total_malloc_and_exit(cmd, s);
	cmd_arr[0] = make_null_str(cmd, s);
	cmd_arr[1] = NULL;
	return (cmd_arr);
}

void	add_inside_quote(char *old, char *new, size_t *i, size_t *j)
{
	if (old[*i] == '\"')
	{
		new[(*j)++] = old[(*i)++];
		while (old[*i] != '\"')
			new[(*j)++] = old[(*i)++];
		new[(*j)++] = old[(*i)++];
	}
	else if (old[*i] == '\'')
	{
		new[(*j)++] = old[(*i)++];
		while (old[*i] != '\'')
			new[(*j)++] = old[(*i)++];
		new[(*j)++] = old[(*i)++];
	}
}

void	free_cmd_and_struct_exit_0(char *cmd, t_shell *s)
{
	t_env	*tmp;

	free(cmd);
	printf("exit\n");
	while (s->envp_list)
	{
		tmp = s->envp_list->next;
		free(s->envp_list->env_content);
		free(s->envp_list->env_name);
		free(s->envp_list);
		s->envp_list = tmp;
	}
	g_status = 0;
	free(s);
	exit(0);
}
