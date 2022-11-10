/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:46 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/15 10:36:18 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	count_malloc_size(char *cmd, size_t *i, size_t *malloc_size)
{
	while (cmd[*i])
	{
		if (cmd[*i] == '\'')
		{
			(*i)++;
			while (cmd[(*i)++] != '\'')
				(*malloc_size)++;
		}
		else if (cmd[*i] == '\"')
		{
			(*i)++;
			while (cmd[(*i)++] != '\"')
				(*malloc_size)++;
		}
		else
		{
			(*malloc_size)++;
			(*i)++;
		}
	}
}

/* new_cmdのmallocを確保する */
static char	*make_new_str(char *cmd, t_shell *s)
{
	size_t	i;
	size_t	malloc_size;
	char	*new;

	malloc_size = 0;
	i = 0;
	count_malloc_size(cmd, &i, &malloc_size);
	new = (char *)malloc(sizeof(char) * malloc_size + 1);
	if (!new)
	{
		free_malloc(s->cmd->cmd_option);
		free_total_malloc_and_exit(NULL, s);
	}
	return (new);
}

static void	case_of_quote(char *new, char *old, size_t *i, size_t *j)
{
	if (old[*i] == '\'')
	{
		(*i)++;
		while (old[*i] != '\'')
			new[(*j)++] = old[(*i)++];
		(*i)++;
	}
	else if (old[*i] == '\"')
	{
		(*i)++;
		while (old[*i] != '\"')
			new[(*j)++] = old[(*i)++];
		(*i)++;
	}
}

static char	*rm_unneeded_quote(char	*old, char *new)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '\'' || old[i] == '\"')
			case_of_quote(new, old, &i, &j);
		else
			new[j++] = old[i++];
	}
	new[j] = '\0';
	return (new);
}

void	rm_quote(t_shell *s)
{
	size_t	i;
	char	*new;
	t_cmd	*tmp;

	tmp = s->cmd;
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_option[i])
		{
			new = make_new_str(tmp->cmd_option[i], s);
			new = rm_unneeded_quote(tmp->cmd_option[i], new);
			free(tmp->cmd_option[i]);
			tmp->cmd_option[i] = new;
			i++;
		}
		tmp = tmp->next;
	}
}
