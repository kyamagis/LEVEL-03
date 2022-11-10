/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_to_cmd_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:48:12 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/25 19:51:39 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define DOLLAR_STR_LEN 1
#define SIZE_DOLLAR_QUESTION_SINE 2

struct s_variables {
	size_t	malloc_size;
	size_t	i;
	size_t	j;
	size_t	k;
};

struct s_rep_variables {
	size_t	j;
	size_t	i;
	bool	flag;
};

static char	*make_new_str(char *cmd, char *search_str, char *env_cont)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(cmd);
	j = ft_strlen(env_cont);
	k = ft_strlen(search_str);
	new = (char *)malloc(sizeof(char) * (i - (k + DOLLAR_STR_LEN) + j) + 1);
	if (!new)
		return (NULL);
	return (new);
}

static void	replace_util(char *new, char *env_cont, size_t *j)
{
	size_t	k;

	k = 0;
	while (env_cont[k])
		new[(*j)++] = env_cont[k++];
}

static char	*replace(char *cmd, char *search_str, char *env_cont)
{
	char					*new;
	struct s_rep_variables	v;

	v.i = 0;
	v.j = 0;
	v.flag = false;
	new = make_new_str(cmd, search_str, env_cont);
	while (cmd[v.i])
	{
		double_quote_check(cmd, v.i, &(v.flag));
		if (cmd[v.i] == '\'' && v.flag == false)
			add_inside_quote(cmd, new, &(v.i), &(v.j));
		else if (cmd[v.i] == '$')
		{
			v.i += ft_strlen(search_str) + 1;
			replace_util(new, env_cont, &(v.j));
			break ;
		}
		else
			new[(v.j)++] = cmd[(v.i)++];
	}
	while (cmd[v.i])
		new[(v.j)++] = cmd[(v.i)++];
	new[(v.j)] = '\0';
	return (new);
}

static char	*replace_status_char(char *cmd, char *status_str)
{
	char				*new;
	struct s_variables	v;

	v.malloc_size = ft_strlen(cmd) - SIZE_DOLLAR_QUESTION_SINE;
	v.malloc_size += ft_strlen(status_str);
	new = (char *)malloc(sizeof(char) * v.malloc_size + 1);
	if (!new)
		return (NULL);
	v.i = 0;
	v.j = 0;
	while (cmd[v.i])
	{
		if (cmd[v.i] == '$' && cmd[(v.i) + 1] == '?')
		{
			v.k = 0;
			while (status_str[v.k])
				new[(v.j)++] = status_str[(v.k)++];
			(v.i) += 2;
		}
		else
			new[(v.j)++] = cmd[(v.i)++];
	}
	new[v.j] = '\0';
	double_free(cmd, status_str);
	return (new);
}

char	*search_env_and_replace(char *search_str, t_shell *s, char *cmd)
{
	t_env	*env;
	char	*new_cmd;

	env = s->envp_list;
	new_cmd = NULL;
	if (search_str[0] == '?' && search_str[1] == '\0')
		return (replace_status_char(cmd, ft_itoa(g_status)));
	if (search_str[0] == '\0')
		return (cmd);
	while (env)
	{
		if (mini_strstr(search_str, env->env_name))
		{
			new_cmd = replace(cmd, search_str, env->env_content);
			free(cmd);
			if (!new_cmd)
				return (NULL);
			break ;
		}
		env = env->next;
	}
	if (!new_cmd)
		return (no_env_in_list(cmd, search_str));
	return (new_cmd);
}
