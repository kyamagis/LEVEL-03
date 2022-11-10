/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:59:53 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/25 10:42:38 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	mini_strstr(char *str1, char *str2)
{
	size_t	i;

	if (ft_strlen(str1) != ft_strlen(str2))
		return (false);
	i = 0;
	while (str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}

void	check_malloc_error(char *str, char **split, char *cmd, t_shell *s)
{
	if (!str)
	{
		free_malloc(split);
		free_total_malloc_and_exit(cmd, s);
	}
}

size_t	skip_inside_single_quote_2(char *cmd, size_t *index)
{
	size_t	i;

	i = (*index);
	(*index)++;
	while (cmd[*index] != '\'')
		(*index)++;
	i = (*index) - i;
	return (i);
}

static size_t	skip_inside_double_quote_2(char *cmd, size_t	*index)
{
	size_t	i;

	i = (*index);
	(*index)++;
	while (cmd[*index] != '\"')
		(*index)++;
	i = (*index) - i;
	return (i);
}

size_t	skip_quote_finish_second_quote(char *cmd, size_t	*index)
{
	size_t	i;

	i = (*index);
	if (cmd[*index] == '\'')
		skip_inside_single_quote_2(cmd, index);
	else if (cmd[*index] == '\"')
		skip_inside_double_quote_2(cmd, index);
	i = (*index) - i;
	return (i);
}
