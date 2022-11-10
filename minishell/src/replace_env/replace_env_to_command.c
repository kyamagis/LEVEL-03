/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_to_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:53:55 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/25 20:04:53 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_search_str_size(char *cmd, size_t	i)
{
	size_t	search_str_size;

	search_str_size = 0;
	i++;
	while (!(cmd[i] == ' ' || cmd[i] == '\0' || cmd[i] == '\''
			|| cmd[i] == '$' || cmd[i] == '|' || cmd[i++] == '\"'))
		search_str_size++;
	return (search_str_size);
}

void	double_quote_check(char *cmd, size_t index, bool *flag)
{
	if (cmd[index] == '\"')
	{
		if (*flag == false)
			*flag = true;
		else
			*flag = false;
	}
}

char	*replace_env_to_command(char *cmd, t_shell *s)
{
	size_t	i;
	char	*search_str;
	bool	flag;

	i = 0;
	flag = false;
	while (cmd[i])
	{
		double_quote_check(cmd, i, &flag);
		if (cmd[i] == '\'' && flag == false)
			skip_inside_single_quote_2(cmd, &i);
		else if (cmd[i] == '$')
		{
			search_str = make_search_str(cmd, count_search_str_size(cmd, i));
			if (!search_str)
				return (NULL);
			cmd = search_env_and_replace(search_str, s, cmd);
			free(search_str);
			if (!cmd)
				return (NULL);
			break ;
		}
		i++;
	}
	return (cmd);
}

/* true ==  There is an ENV to expand */
static bool	is_there_dollar_sign(char *cmd)
{
	bool	flag;
	size_t	i;

	flag = false;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
			{
				if (cmd[i] == '$')
					return (true);
				i++;
			}
		}
		else if (cmd[i] == '\'')
			skip_inside_single_quote_2(cmd, &i);
		else if (cmd[i] == '$')
			return (true);
		i++;
	}
	return (flag);
}

char	**replace_env(char **cmd_arr, t_shell *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd_arr[i])
	{
		j = 0;
		while (cmd_arr[i][j])
		{
			if (is_there_dollar_sign(cmd_arr[i]))
			{
				cmd_arr[i] = replace_env_to_command(cmd_arr[i], s);
				if (!(cmd_arr[i]))
				{
					cmd_arr[i] = make_null_str(NULL, s);
					break ;
				}
			}
			j++;
		}
		i++;
	}
	return (cmd_arr);
}
