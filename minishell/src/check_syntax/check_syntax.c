/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:11:47 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 16:46:12 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	is_there_continuous_pipe(char *cmd, t_shell *s)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '|')
		{
			if (cmd[i + 1] == '|')
				put_error("syntax error near unexpected token '|'\n", cmd, s);
			else if (cmd[i + 1] == ' ')
			{
				while (cmd[i + 1] == ' ')
				{
					if (cmd[i + 1] == '|')
						put_error("syntax error\n", cmd, s);
					i++;
				}
			}
		}
		i++;
	}
}

static size_t	count_malloc_size(char *cmd)
{
	size_t	malloc_size;
	size_t	i;

	malloc_size = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			malloc_size += skip_quote(cmd, &i);
		else if (cmd[i] == '<' && cmd[i + 1] == '>')
			i++;
		else
		{
			malloc_size++;
			i++;
		}
	}
	return (malloc_size);
}

static char	*ass_right_cmd(char *cmd, t_shell *s)
{
	char	*new;
	size_t	malloc_size;
	size_t	i;
	size_t	j;

	malloc_size = count_malloc_size(cmd);
	new = (char *)malloc(sizeof(char) * malloc_size + 1);
	if (!new)
		put_error("malloc error\n", cmd, s);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			add_inside_quote(cmd, new, &i, &j);
		else if (cmd[i] == '<' && cmd[i + 1] == '>')
			i++;
		else
			new[j++] = cmd[i++];
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}

static char	*is_there_invalid_redirection(char *cmd, t_shell *s)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '<' && cmd[i + 1] == '>')
			return (ass_right_cmd(cmd, s));
		i++;
	}
	return (cmd);
}

char	*syntax_check(char *cmd, t_shell *s)
{
	is_there_continuous_pipe(cmd, s);
	syntax_check2(cmd, s);
	check_syntax3(cmd, s);
	cmd = is_there_invalid_redirection(cmd, s);
	return (cmd);
}
