/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:19:17 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/24 19:55:56 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	is_there_rd_sign_at_end(char *cmd, t_shell *s)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(cmd);
	cmd_len--;
	if (cmd[cmd_len] == '<' || cmd[cmd_len] == '>')
		put_error("parse error\n", cmd, s);
}

static void	check_consecutive(char *cmd, t_shell *s, char c, size_t *index)
{
	size_t	count;

	count = 0;
	if (cmd[*index] == '\"' || cmd[*index] == '\'')
		skip_quote_finish_second_quote(cmd, index);
	else if (cmd[*index] == c)
	{
		while (cmd[(*index)] == c)
		{
			(*index)++;
			count++;
		}
		if (count >= 3)
			put_error("parse error\n", cmd, s);
		else
			(*index) -= count;
	}
}

static void	is_there_three_more_consecutive_rd_sigh(char *cmd, t_shell*s)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		check_consecutive(cmd, s, '<', &i);
		i++;
	}
	i = 0;
	while (cmd[i])
	{
		check_consecutive(cmd, s, '>', &i);
		i++;
	}
}

static void	is_there_escape(char *cmd, t_shell *s)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '\\')
			put_error("'\\' outside of QUOTE is not supported\n", cmd, s);
		i++;
	}
}

void	syntax_check2(char *cmd, t_shell *s)
{
	is_there_escape(cmd, s);
	is_there_rd_sign_at_end(cmd, s);
	is_there_three_more_consecutive_rd_sigh(cmd, s);
}
