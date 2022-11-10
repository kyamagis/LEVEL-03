/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_valid_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:24:42 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/19 22:30:58 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static size_t	count_valid_pipe(char *cmd)
{
	size_t	i;
	size_t	malloc_size;

	i = 0;
	malloc_size = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] == '\\' && cmd[i + 1] == '|')
			i += 2;
		else if (cmd[i] == '|')
			malloc_size++;
		i++;
	}
	return (malloc_size);
}

static char	*word_dup(char *str, int start, int finish, char **test)
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

static char	**init_split(char *cmd, t_shell *s)
{
	char	**split;
	size_t	malloc_size;

	malloc_size = 1;
	malloc_size += count_valid_pipe(cmd);
	split = (char **)malloc(sizeof(char *) * (malloc_size + 1));
	if (!(split))
		free_tmp_cmds(cmd, s);
	split[malloc_size] = NULL;
	return (split);
}

char	**split_with_valid_pipe(char *cmd, t_shell *s)
{
	int		index;
	size_t	i;
	size_t	j;
	char	**split;

	i = 0;
	j = 0;
	index = check_first_is_quote(cmd[0]);
	split = init_split(cmd, s);
	while (i <= ft_strlen(cmd))
	{
		if ((cmd[i] == '\"' || cmd[i] == '\'') && index >= 0)
			skip_quote_finish_second_quote(cmd, &i);
		else if (cmd[i] != '|' && index < 0)
			case_of_no_delimiter(cmd, &index, &i, '|');
		else if ((cmd[i] == '|' || i == ft_strlen(cmd)) && index >= 0)
		{
			split[j] = word_dup(cmd, index, i, split);
			if (!split[j++])
				return (NULL);
			index = -1;
		}
		i++;
	}
	return (split);
}
