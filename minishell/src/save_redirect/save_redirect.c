/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:35:05 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 16:16:29 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define QUOTE_YES 2
#define QUOTE_NO 1

static size_t	count_pipe(char *cmd_line)
{
	size_t	i;
	size_t	pipe_count;

	i = 0;
	pipe_count = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
			skip_quote_finish_second_quote(cmd_line, &i);
		else if (cmd_line[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

static size_t	count_rd(char *cmd)
{
	size_t	i;
	size_t	count_redirect;

	i = 0;
	count_redirect = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '<' && cmd[i + 1] != '<')
			count_redirect++;
		else if (cmd[i] == '>' && cmd[i + 1] != '>')
			count_redirect++;
		else if ((cmd[i] == '<' && cmd[i + 1] == '<')
			|| (cmd[i] == '>' && cmd[i + 1] == '>'))
		{
			count_redirect++;
			i++;
		}
		i++;
	}
	if (count_redirect == 0)
		count_redirect++;
	return (count_redirect);
}

static size_t	*make_rd_flag_arr(char **rd_strs, size_t *redirect_flag_arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (rd_strs[i])
	{
		j = 0;
		redirect_flag_arr[i] = QUOTE_NO;
		if (rd_strs[i][j] != '\0')
		{
			while (rd_strs[i][j])
			{
				if (rd_strs[i][j] == '\"' || rd_strs[i][j] == '\'')
					redirect_flag_arr[i] = QUOTE_YES;
				j++;
			}
		}
		i++;
	}
	redirect_flag_arr[i] = 0;
	return (redirect_flag_arr);
}

static void	make_second_malloc(char *cmd, t_shell *s)
{
	size_t	i;
	size_t	*rd_flag_arr;
	char	**rd_arr;

	s->tmp_arr = split_with_valid_pipe(cmd, s);
	if (!s->tmp_arr)
		free_tmp_cmds(cmd, s);
	i = 0;
	while (i <= s->pipe_count)
	{
		rd_arr = (char **)malloc(sizeof(char *)
				* (count_rd(s->tmp_arr[i]) + 1));
		if (!rd_arr)
			free_total_malloc_and_exit(cmd, s);
		rd_flag_arr = (size_t *)malloc(sizeof(size_t)
				* (count_rd(s->tmp_arr[i]) + 1));
		if (!rd_arr)
			free_total_malloc_and_exit(cmd, s);
		s->tmp_rd_cmd[i] = make_rd_arr(s->tmp_arr[i], rd_arr, cmd, s);
		s->tmp_rd_cmd_flag[i] = make_rd_flag_arr(s->tmp_rd_cmd[i], rd_flag_arr);
		s->tmp_rd_cmd[i] = rm_quote_from_rd_str(s->tmp_rd_cmd[i], cmd, s);
		i++;
	}
	free_malloc(s->tmp_arr);
}

/* リダイレクト文字列を別に保存。リダイレクト文字が削除されたコマンドが返る */
void	save_redirect(char *cmd, t_shell *s)
{
	s->pipe_count = count_pipe(cmd);
	s->tmp_rd_cmd = (char ***)malloc(sizeof(char **)
			* ((s->pipe_count + 1) + 1));
	if (!s->tmp_rd_cmd)
		free_cmd_and_struct_exit(cmd, s);
	s->tmp_rd_cmd[s->pipe_count + 1] = NULL;
	s->tmp_rd_cmd_flag = malloc(sizeof(size_t *) * ((s->pipe_count + 1) + 1));
	if (!s->tmp_rd_cmd_flag)
		free_cmd_and_struct_exit(cmd, s);
	s->tmp_rd_cmd_flag[s->pipe_count + 1] = NULL;
	make_second_malloc(cmd, s);
}
