/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_cmd_without_redirect.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:41:33 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 19:28:22 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define QUOTE_YES 2

static size_t	count_space_before_rd_str(char *cmd)
{
	size_t	i;
	size_t	space_size_before_rd_str;

	i = 0;
	space_size_before_rd_str = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		if (cmd[i] == ' ' && (cmd[i + 1] == '<' || cmd[i + 1] == '>'))
			space_size_before_rd_str++;
		i++;
	}
	return (space_size_before_rd_str);
}

static size_t	count_malloc_size(char *cmd, size_t cmd_size, t_shell *s)
{
	size_t	i;
	size_t	j;
	size_t	total_rd_str_size;
	size_t	space_size_before_rd_str;

	i = 0;
	total_rd_str_size = 0;
	space_size_before_rd_str = count_space_before_rd_str(cmd);
	while (s->tmp_rd_cmd[i])
	{
		j = 0;
		while (s->tmp_rd_cmd[i][j])
		{
			total_rd_str_size += ft_strlen(s->tmp_rd_cmd[i][j]);
			if (s->tmp_rd_cmd_flag[i][j] == QUOTE_YES)
				total_rd_str_size += 2;
			j++;
		}
		i++;
	}
	i = cmd_size - total_rd_str_size - space_size_before_rd_str;
	return (i);
}

static void	assign_to_new_str(char *old, char *new, size_t *i, size_t *j)
{
	while (old[*i])
	{
		if (old[*i] == '\"' || old[*i] == '\'')
			add_inside_quote(old, new, i, j);
		else if (old[*i] == '<' || old[*i] == '>')
		{
			(*i)++;
			if (old[*i] == '<' || old[*i] == '>')
				(*i)++;
			if (old[*i] == '\"' || old[*i] == '\'')
				skip_quote(old, i);
			while (!(old[*i] == ' ' || old[*i] == '|'
					|| old[*i] == '\0' || old[*i] == '>' || old[*i] == '<'))
			(*i)++;
		}
		else if (old[*i] == ' '
			&& (old[(*i) + 1] == '<' || old[(*i) + 1] == '>'))
			(*i)++;
		else
			new[(*j)++] = old[(*i)++];
	}
}

static char	*rm_redirect_str(char *cmd, char *new_cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	assign_to_new_str(cmd, new_cmd, &i, &j);
	new_cmd[j] = '\0';
	return (new_cmd);
}

/* リダイレクト文字を除去したコマンドを返す */
char	*make_new_cmd_without_redirect(char *cmd, t_shell *s)
{
	char	*new_cmd;
	size_t	cmd_size;
	size_t	malloc_size;

	cmd_size = ft_strlen(cmd);
	malloc_size = count_malloc_size(cmd, cmd_size, s);
	if (malloc_size)
	{
		new_cmd = (char *)malloc(sizeof(char) * malloc_size + 1);
		if (!new_cmd)
			free_total_malloc_and_exit(cmd, s);
		new_cmd = rm_redirect_str(cmd, new_cmd);
	}
	else
		new_cmd = make_null_str(cmd, s);
	free(cmd);
	return (new_cmd);
}
