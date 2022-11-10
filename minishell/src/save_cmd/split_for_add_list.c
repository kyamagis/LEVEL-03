/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_add_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:00:21 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/15 12:58:07 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct s_variables {
	size_t	i;
	size_t	j;
	int		index;
};

static int	count_words(char *str, char c)
{
	int		rtn_num;
	int		trigger;
	size_t	i;

	rtn_num = 0;
	trigger = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' )
			skip_quote_finish_second_quote(str, &i);
		if (str[i] != c && trigger == 0)
		{
			trigger = 1;
			rtn_num++;
		}
		else if (str[i] == c)
			trigger = 0;
		i++;
	}
	return (rtn_num);
}

static char	*word_dup(char *str, int start, int finish, char **test)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
	{
		free_malloc(test);
		return (NULL);
	}
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**init_split(char *s, char c)
{
	char	**split;
	size_t	malloc_size;

	malloc_size = count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (malloc_size + 1));
	if (!(split))
		return (NULL);
	split[malloc_size] = NULL;
	return (split);
}

void	case_of_no_delimiter(char *s, int *index, size_t *i, char c)
{
	*index = *i;
	if ((s[*i] == '\"' || s[*i] == '\'') && s[(*i) - 1] == c)
		skip_quote_finish_second_quote(s, i);
}

char	**split_for_add_list(char *s, char c)
{
	struct s_variables	v;
	char				**split;

	v.i = 0;
	v.j = 0;
	v.index = check_first_is_quote(s[0]);
	split = init_split(s, c);
	if (!split)
		return (NULL);
	while (v.i <= ft_strlen(s))
	{
		if ((s[v.i] == '\"' || s[v.i] == '\'') && v.index >= 0)
			skip_quote_finish_second_quote(s, &(v.i));
		if (s[v.i] != c && v.index < 0)
			case_of_no_delimiter(s, &(v.index), &(v.i), ' ');
		else if ((s[v.i] == c || v.i == ft_strlen(s)) && v.index >= 0)
		{
			split[v.j] = word_dup(s, v.index, v.i, split);
			if (!split[(v.j)++])
				return (NULL);
			v.index = -1;
		}
		(v.i)++;
	}
	return (split);
}
