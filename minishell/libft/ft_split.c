/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:00:33 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/19 22:55:01 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	*malloc_error(char **malloc)
{
	unsigned int	i;

	i = 0;
	while (malloc[i])
	{
		free(malloc[i]);
		i++;
	}
	free(malloc);
	return (NULL);
}

static int	count_words(const char *str, char c)
{
	int		rtn_num;
	int		trigger;
	size_t	i;

	rtn_num = 0;
	trigger = 0;
	i = 0;
	while (str[i])
	{
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

static char	*word_dup(const char *str, int start, int finish, char **test)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
	{
		malloc_error(test);
		return (NULL);
	}
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**init_split(char const *s, char c)
{
	char	**split;
	size_t	malloc_size;

	malloc_size = count_words(s, c);
	if (!(s))
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (malloc_size + 1));
	if (!(split))
		return (NULL);
	split[malloc_size] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	size_t	i;
	size_t	j;
	char	**split;

	i = 0;
	j = 0;
	index = -1;
	split = init_split(s, c);
	if (!split)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j] = word_dup(s, index, i, split);
			if (!split[j++])
				return (NULL);
			index = -1;
		}
		i++;
	}
	return (split);
}
