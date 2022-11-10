/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:14:11 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/15 10:36:18 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	quote_num_check(char *cmd, size_t *i, t_shell *s)
{
	if (cmd[*i] == '\"')
	{
		(*i)++;
		while (!(cmd[*i] == '\"' || cmd[*i] == '\0'))
			(*i)++;
	}
	else if (cmd[*i] == '\'')
	{
		(*i)++;
		while (!(cmd[*i] == '\'' || cmd[*i] == '\0'))
			(*i)++;
	}
	if (cmd[*i] == '\0')
	{
		printf("quote error\n");
		free_cmd_and_struct_exit(cmd, s);
	}
}

/* quoteの数が合わなければエラーを出す */
void	quote_check(char *cmd, t_shell *s)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'' )
			quote_num_check(cmd, &i, s);
		i++;
	}
}
