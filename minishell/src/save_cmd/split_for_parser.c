/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:44:46 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 19:31:44 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct s_variables {
	size_t	i;
	size_t	j;
	int		index;
};

static char	*word_dup(char *cmd, size_t start, size_t finish)
{
	char	*word;
	size_t	i;

	word = (char *)malloc(sizeof(char) * ((finish - start) + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = cmd[start++];
	word[i] = '\0';
	return (word);
}

static char	*add_null_str(char **split, char *cmd, t_shell *s)
{
	char	*null_str;

	null_str = (char *)malloc(sizeof(char) * 1);
	if (!null_str)
	{
		free_malloc(split);
		free_total_malloc_and_exit(cmd, s);
	}
	null_str[0] = '\0';
	return (null_str);
}

static size_t	count_malloc_size(char *cmd, size_t *i)
{
	size_t	malloc_size;

	malloc_size = 1;
	while (cmd[*i])
	{
		if (cmd[*i] == '\"' || cmd[*i] == '\'')
			skip_quote_finish_second_quote(cmd, i);
		else if (cmd[*i] == '|')
			malloc_size++;
		(*i)++;
	}
	return (malloc_size);
}

static char	**init_split(char *cmd, t_shell *s, size_t *i, size_t *j)
{
	char	**split;
	size_t	malloc_size;

	malloc_size = count_malloc_size(cmd, i);
	split = (char **)malloc(sizeof(char *) * (malloc_size + 1));
	if (!(split))
		free_total_malloc_and_exit(cmd, s);
	split[malloc_size] = NULL;
	if (cmd[(*i) - 1] == '|')
	{
		split[malloc_size - 1] = add_null_str(split, cmd, s);
		*i = 0;
	}
	else if (cmd[0] == '|')
	{
		split[(*j)++] = add_null_str(split, cmd, s);
		*i = 1;
	}
	else
		*i = 0;
	return (split);
}

char	**split_for_parser(char *cmd, t_shell *s)
{
	struct s_variables	v;
	char				**split;

	v.i = 0;
	v.j = 0;
	v.index = check_first_is_quote(cmd[0]);
	split = init_split(cmd, s, &(v.i), &(v.j));
	while (v.i <= ft_strlen(cmd))
	{
		if ((cmd[v.i] == '\"' || cmd[v.i] == '\'') && v.index >= 0)
			skip_quote_finish_second_quote(cmd, &(v.i));
		if (cmd[v.i] == '|' && cmd[v.i - 1] == '|' )
			split[(v.j)++] = add_null_str(split, cmd, s);
		else if (cmd[v.i] != '|' && v.index < 0)
			case_of_no_delimiter(cmd, &(v.index), &(v.i), '|');
		else if (v.index >= 0 && (cmd[v.i] == '|' || cmd[v.i] == '\0'))
		{
			split[v.j] = word_dup(cmd, v.index, v.i);
			check_malloc_error(split[(v.j)++], split, cmd, s);
			v.index = -1;
		}
		(v.i)++;
	}
	return (split);
}
