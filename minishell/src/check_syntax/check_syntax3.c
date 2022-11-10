/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:27:10 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 16:42:11 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_error(char *err_str, char *cmd, t_shell *s)
{
	printf("%s", err_str);
	free_cmd_and_struct_exit(cmd, s);
}

static void	is_there_wrong_rd_sign(char *cmd, t_shell *s)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '>' && cmd[i + 1] == '<')
			put_error("parse error\n", cmd, s);
		else if (cmd[i] == '<' && cmd[i + 1] == '>' && cmd[i + 2] == '>')
			put_error("parse error\n", cmd, s);
		i++;
	}
}

static void	is_there_continuous_dollar(char *cmd, t_shell *s)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '$' && cmd[i + 1] == '$')
			put_error("'$$' is not supported\n", cmd, s);
		i++;
	}
}

static void	is_there_pipe_at_start_and_end(char *cmd, t_shell *s)
{
	size_t	cmd_len;

	if (cmd[0] == '|')
		put_error("syntax error\n", cmd, s);
	cmd_len = ft_strlen(cmd);
	if (cmd[cmd_len - 1] == '|')
		put_error("syntax error\n", cmd, s);
}

void	check_syntax3(char *cmd, t_shell *s)
{
	is_there_pipe_at_start_and_end(cmd, s);
	is_there_wrong_rd_sign(cmd, s);
	is_there_continuous_dollar(cmd, s);
}
