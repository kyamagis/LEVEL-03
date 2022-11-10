/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redirect_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:51:41 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 17:14:44 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_quote(char *old, char *new)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '\"')
		{
			i++;
			while (old[i] != '\"')
				new[j++] = old[i++];
			i++;
		}
		else if (old[i] == '\'')
		{
			i++;
			while (old[i] != '\'')
				new[j++] = old[i++];
			i++;
		}
		else
			new[j++] = old[i++];
	}
	return (new);
}

static char	**make_new_arr(char **rd_arr, char *cmd_line, t_shell *s)
{
	char	**rtn_arr;
	size_t	malloc_size;
	size_t	i;

	i = 0;
	malloc_size = 0;
	while (rd_arr[i++])
		malloc_size++;
	rtn_arr = (char **)malloc(sizeof(char *) * (malloc_size + 1));
	if (!rtn_arr)
		free_total_malloc_and_exit(cmd_line, s);
	rtn_arr[malloc_size] = NULL;
	return (rtn_arr);
}

static void	count_malloc_size_util(
	char *rd_str, size_t *i, size_t *malloc_size, char c)
{
	(*i)++;
	while (rd_str[*i] != c)
	{
		(*i)++;
		(*malloc_size)++;
	}
	(*i)++;
}

static size_t	count_malloc_size(char *rd_str)
{
	size_t	malloc_size;
	size_t	i;

	malloc_size = 0;
	i = 0;
	while (rd_str[i])
	{
		if (rd_str[i] == '\"')
			count_malloc_size_util(rd_str, &i, &malloc_size, '\"');
		else if (rd_str[i] == '\'')
			count_malloc_size_util(rd_str, &i, &malloc_size, '\'');
		else
		{
			i++;
			malloc_size++;
		}
	}
	return (malloc_size);
}

char	**rm_quote_from_rd_str(char **old_arr, char *cmd_line, t_shell *s)
{
	size_t	i;
	size_t	malloc_size;
	char	**new_arr;

	i = 0;
	new_arr = make_new_arr(old_arr, cmd_line, s);
	while (old_arr[i])
	{
		malloc_size = count_malloc_size(old_arr[i]);
		new_arr[i] = (char *)malloc(sizeof(char) * ((malloc_size) + 1));
		if (!new_arr[i])
		{
			free_malloc(new_arr);
			free_total_malloc_and_exit(cmd_line, s);
		}
		new_arr[i][malloc_size] = '\0';
		if (old_arr[i][0] != '\0')
			new_arr[i] = remove_quote(old_arr[i], new_arr[i]);
		i++;
	}
	free_malloc(old_arr);
	return (new_arr);
}
