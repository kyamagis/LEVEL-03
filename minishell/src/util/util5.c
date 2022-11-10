/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:02:28 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/25 20:12:02 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct s_make_search_str_v {
	char	*search_str;
	size_t	i;
	size_t	j;
	bool	flag;
};

void	double_free(char *str, char *str2)
{
	free(str);
	free(str2);
}

char	*make_search_str(char *cmd, size_t search_str_size)
{
	struct s_make_search_str_v	v;

	v.search_str = (char *)malloc(sizeof(char) * search_str_size + 1);
	if (!(v.search_str))
		return (NULL);
	v.i = 0;
	v.j = 0;
	v.flag = false;
	while (cmd[v.i])
	{
		double_quote_check(cmd, v.i, &(v.flag));
		if (cmd[v.i] == '\'' && v.flag == false)
			skip_inside_single_quote_2(cmd, &(v.i));
		else if (cmd[v.i] == '$')
		{
			(v.i)++;
			while (!(cmd[v.i] == ' ' || cmd[v.i] == '\0' || cmd[v.i] == '\''
					|| cmd[v.i] == '$' || cmd[v.i] == '|' || cmd[v.i] == '\"'))
				v.search_str[(v.j)++] = cmd[(v.i)++];
			break ;
		}
		(v.i)++;
	}
	v.search_str[v.j] = '\0';
	return (v.search_str);
}
