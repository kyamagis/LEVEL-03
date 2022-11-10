/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:42:41 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 11:38:08 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	case_of_redirect(char *cmd, char *new_cmd, size_t *i, size_t *j)
{
	if (cmd[*i + 1 == ' '])
	{
		new_cmd[(*j)++] = cmd[(*i)++];
		while (cmd[*i] == ' ')
			(*i)++;
	}
	if (cmd[*i] == '\"')
	{
		new_cmd[(*j)++] = cmd[(*i)++];
		while (cmd[*i] != '\"')
			new_cmd[(*j)++] = cmd[(*i)++];
		new_cmd[(*j)++] = cmd[(*i)++];
	}
}

static void	case_of_space_or_pipe(char *cmd, char *new, size_t *i, size_t *j)
{
	if (cmd[*i] == ' ')
	{
		while (cmd[*i + 1] == ' ')
		(*i)++;
		if (cmd[*i + 1] == '|')
			(*i)++;
		else
			new[(*j)++] = cmd[(*i)++];
	}
	else if (cmd[*i] == '|')
	{
		new[(*j)++] = cmd[(*i)++];
		while (cmd[*i] == ' ')
			(*i)++;
	}
}

static size_t	count_space(char *cmd)
{
	size_t	num_space;
	size_t	i;

	i = 0;
	num_space = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote(cmd, &i);
		else if (cmd[i] == '|' && cmd[i] == ' ')
			num_space++;
		else if ((cmd[i] == '<' || cmd[i] == '>') && cmd[i] == ' ')
			num_space++;
		else if (cmd[i] == ' ')
		{
			while (cmd[i++ + 1] == ' ')
				num_space++;
			if (cmd[i] == '|')
				num_space++;
		}
		else
			i++;
	}
	return (num_space);
}

static char	*make_malloc(char *cmd, t_shell *s)
{
	char	*new_cmd;
	size_t	cmd_size;
	size_t	total_space_size;

	cmd_size = ft_strlen(cmd);
	total_space_size = count_space(cmd);
	new_cmd = (char *)malloc(sizeof(char) * (cmd_size - total_space_size) + 1);
	if (!new_cmd)
		free_cmd_and_struct_exit(cmd, s);
	return (new_cmd);
}

/* スペースを削除した新しい文字列を確保する */
char	*rm_space(char *cmd, t_shell *s)
{
	size_t	i;
	size_t	j;
	char	*new_cmd;

	i = 0;
	j = 0;
	new_cmd = make_malloc(cmd, s);
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			add_inside_quote(cmd, new_cmd, &i, &j);
		else if (cmd[i] == '>' || cmd[i] == '<')
			case_of_redirect(cmd, new_cmd, &i, &j);
		else if (cmd[i] == ' ' || cmd[i] == '|' )
			case_of_space_or_pipe(cmd, new_cmd, &i, &j);
		else
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = '\0';
	free(cmd);
	return (new_cmd);
}
