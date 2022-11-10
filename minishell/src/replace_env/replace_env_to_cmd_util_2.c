/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_to_cmd_util_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:31:06 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/25 20:03:56 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define DOLLAR_STR_LEN 1
#define DOLLAR_AND_SPACE_LEN 2

struct s_skip_env_str_v {
	size_t	i;
	size_t	j;
	bool	flag;
};

static void	case_of_nothing_match(char *cmd, char *new, size_t *i, size_t *j)
{
	while (!(cmd[(*i) + 1] == ' ' || cmd[(*i) + 1] == '\0'
			|| cmd[(*i) + 1] == '$'))
	{
			new[(*j)++] = cmd[(*i)++];
	}
}

static void	add_env_in_single_quote(
	char *new, char *old, size_t *i, size_t *j)
{
	new[(*j)++] = old[(*i)++];
	while (old[(*i)] != '\'')
		new[(*j)++] = old[(*i)++];
}

static char	*skip_env_str(char *new, char *cmd, char *search_str, size_t len)
{
	struct s_skip_env_str_v	v;

	v.i = 0;
	v.j = 0;
	while (cmd[v.i])
	{
		double_quote_check(cmd, v.i, &(v.flag));
		if (cmd[v.i] == '\'' && v.flag == false)
			add_env_in_single_quote(new, cmd, &(v.i), &(v.j));
		if (cmd[v.i] == '$')
		{
			if (check_str_match(cmd, v.i + 1, search_str))
			{
				v.i += len + DOLLAR_STR_LEN;
				if (cmd[v.i] == ' ')
					v.i += 1;
			}
			else
				case_of_nothing_match(cmd, new, &(v.i), &(v.j));
		}
		else
			new[(v.j)++] = cmd[(v.i)++];
	}
	return (new);
}

static size_t	count_malloc_size(char *cmd, char *search_str, bool flag)
{
	size_t	malloc_size;
	size_t	i;

	i = 0;
	malloc_size = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			malloc_size += skip_inside_single_quote(cmd, &i);
		else if (cmd[i] == '$')
		{
			count_m_size_u(cmd, search_str, &i, &flag);
			if (flag)
				break ;
		}
		else
		{
			i++;
			malloc_size++;
		}
	}
	while (cmd[i++])
		malloc_size++;
	return (malloc_size);
}

char	*no_env_in_list(char *cmd, char *search_str)
{
	char	*new_cmd;
	size_t	malloc_size;
	bool	flag;

	flag = false;
	malloc_size = count_malloc_size(cmd, search_str, flag);
	if (malloc_size != 0)
	{
		new_cmd = (char *)malloc(sizeof(char) * malloc_size + 1);
		if (!new_cmd)
			return (NULL);
		new_cmd[malloc_size] = '\0';
		skip_env_str(new_cmd, cmd, search_str, ft_strlen(search_str));
	}
	else
		new_cmd = NULL;
	free(cmd);
	return (new_cmd);
}
