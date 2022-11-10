/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:09:11 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/24 18:58:52 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_first_is_quote(char c)
{
	int	index;

	index = -1;
	if (c == '\'' || c == '\"')
		index = 0;
	return (index);
}

char	*add_final_char_str(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	str[0] = '\0';
	return (str);
}

size_t	skip_inside_single_quote(char *cmd, size_t *index)
{
	size_t	i;

	i = (*index);
	(*index)++;
	while (cmd[*index] != '\'')
		(*index)++;
	(*index)++;
	i = (*index) - i;
	return (i);
}

size_t	skip_quote(char *cmd, size_t	*index)
{
	size_t	i;

	i = (*index);
	if (cmd[*index] == '\'')
		skip_inside_single_quote(cmd, index);
	else if (cmd[*index] == '\"')
		skip_inside_double_quote(cmd, index);
	i = (*index) - i;
	return (i);
}

void	status_on_and_exit(t_shell *s)
{
	g_status = 1;
	free(s);
	exit(1);
}
