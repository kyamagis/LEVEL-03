/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:39:08 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 10:40:16 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	count_rd_sign(char *cmd, size_t *i, size_t *rd_str_size)
{
	if ((cmd[*i] == '<' && cmd[(*i) + 1] == '<')
		|| (cmd[*i] == '>' && cmd[(*i) + 1] == '>'))
	{
		(*rd_str_size) += 2;
		(*i) += 2;
	}
	else if ((cmd[*i] == '<' && cmd[(*i) + 1] != '<')
		|| (cmd[*i] == '>' && cmd[(*i) + 1] != '>'))
	{
		(*rd_str_size)++;
		(*i)++;
	}
}

static size_t	count_redirect_str_size(char *cmd, size_t i)
{
	size_t	redirect_str_size;

	redirect_str_size = 0;
	count_rd_sign(cmd, &i, &redirect_str_size);
	if (cmd[i] == ' ')
		i++;
	while (!(cmd[i] == ' ' || cmd[i] == '\0'
			|| cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<'))
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			redirect_str_size += skip_quote(cmd, &i);
		else
		{
			redirect_str_size++;
			i++;
		}
	}
	return (redirect_str_size);
}

static void	assign_to_new_str(char *old, char *new, size_t *i, size_t *j)
{
	while (!(old[*i] == ' ' || old[*i] == '\0' || old[*i] == '|'))
	{
		if (old[*i] == '<' || old[*i] == '>')
		{
			while (old[*i] == '<')
				new[(*j)++] = old[(*i)++];
			while (old[*i] == '>')
				new[(*j)++] = old[(*i)++];
			if (old[*i] == ' ')
				i++;
		}
		else if (old[*i] == '\"')
		{
			new[(*j)++] = old[(*i)++];
			while (old[*i] != '\"')
				new[(*j)++] = old[(*i)++];
			new[(*j)++] = old[(*i)++];
		}
		else
			new[(*j)++] = old[(*i)++];
		if (old[*i] == '<' || old[*i] == '>')
			break ;
	}
}

static char	*make_rd_str(char *cmd, size_t index, char *cmd_line, t_shell *s)
{
	char	*rd_str;
	size_t	j;

	j = count_redirect_str_size(cmd, index);
	rd_str = (char *)malloc(sizeof(char) * j + 1);
	if (!rd_str)
		free_total_malloc_and_exit(cmd_line, s);
	j = 0;
	assign_to_new_str(cmd, rd_str, &index, &j);
	rd_str[j] = '\0';
	return (rd_str);
}

char	**make_rd_arr(char *cmd, char **rd_str, char *cmd_line, t_shell *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '<' && cmd[i + 1] != '<')
			rd_str[j++] = make_rd_str(cmd, i, cmd_line, s);
		else if (cmd[i] == '>' && cmd[i + 1] != '>')
			rd_str[j++] = make_rd_str(cmd, i, cmd_line, s);
		else if ((cmd[i] == '<' && cmd[i + 1] == '<')
			|| (cmd[i] == '>' && cmd[i + 1] == '>'))
		{
			rd_str[j++] = make_rd_str(cmd, i, cmd_line, s);
			i++;
		}
		i++;
	}
	if (j == 0)
		rd_str[j++] = add_final_char_str();
	rd_str[j] = NULL;
	return (rd_str);
}
