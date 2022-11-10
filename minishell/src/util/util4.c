/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:14:57 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/25 20:02:26 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_no_pipe_char(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '|')
			return (false);
		i++;
	}
	return (true);
}

/* ADDING 2 in malloc is for taking cmd's amount */
static char	**make_null_arr2(char *cmd, t_shell *s)
{
	char	**rtn;
	size_t	i;

	rtn = (char **)malloc(sizeof(char *) * (ft_strlen(cmd) + 2));
	if (!rtn)
		free_total_malloc_and_exit(cmd, s);
	i = 0;
	while (i <= ft_strlen(cmd))
	{
		rtn[i] = (char *)malloc(sizeof(char) * 1);
		if (!rtn[i])
		{
			free_malloc(rtn);
			free_total_malloc_and_exit(cmd, s);
		}
		rtn[i][0] = '\0';
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

char	**check_new_line(char *cmd_line, t_shell *s)
{
	char	**cmd_arr;

	if (cmd_line[0] == '\0')
		cmd_arr = make_null_arr(cmd_line, s);
	else if (check_no_pipe_char(cmd_line))
		cmd_arr = make_null_arr2(cmd_line, s);
	else
		cmd_arr = split_for_parser(cmd_line, s);
	free(cmd_line);
	return (cmd_arr);
}

bool	check_str_match(char *str, size_t index, char *search_str)
{
	size_t	i;

	i = 0;
	while (!(str[index] == ' ' || str[index] == '\0' || str[index] == '\''
			|| str[index] == '$' || str[index] == '"'))
	{
		if (str[index] != search_str[i])
			return (false);
		index++;
		i++;
	}
	return (true);
}

void	count_m_size_u(
	char *cmd, char *search_str, size_t *i, bool *flag)
{
	size_t	s_size;

	if (check_str_match(cmd, (*i) + 1, search_str))
	{
		s_size = ft_strlen(search_str);
		(*i) += s_size + 1;
		if (cmd[*i] == ' ')
			(*i) += 1;
		*flag = true;
	}
	else
		(*i)++;
}
