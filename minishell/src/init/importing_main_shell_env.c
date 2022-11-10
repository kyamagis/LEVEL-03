/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   importing_main_shell_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:04:04 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/15 10:35:52 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define BEFORE 0
#define AFTER 1

static void	all_free(char **split, t_shell *s)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	status_on_and_exit(s);
}

static char	*make_str(char *env_line, size_t str_size, size_t	flag)
{
	size_t	i;
	size_t	j;
	char	*tmp_str;

	tmp_str = (char *)malloc(sizeof(char) * str_size + 1);
	if (!tmp_str)
		return (NULL);
	i = 0;
	j = 0;
	if (flag == BEFORE)
		while (env_line[i] != '=')
			tmp_str[j++] = env_line[i++];
	else
	{
		while (env_line[i] != '=')
			i++;
		i++;
		while (env_line[i])
			tmp_str[j++] = env_line[i++];
	}
	tmp_str[j] = '\0';
	return (tmp_str);
}

static char	**split_with_first_equal_sign(char *env_line, t_shell *s)
{
	size_t	i;
	char	**split;
	size_t	str_size;

	split = (char **)malloc(sizeof(char *) * 3);
	if (!split)
		status_on_and_exit(s);
	split[2] = NULL;
	str_size = 0;
	i = 0;
	while (env_line[i++] != '=')
		str_size++;
	split[0] = make_str(env_line, str_size, BEFORE);
	if (!split[0])
		all_free(split, s);
	str_size = 0;
	while (env_line[i++])
		str_size++;
	split[1] = make_str(env_line, str_size, AFTER);
	if (!split[1])
		all_free(split, s);
	return (split);
}

static t_env	*new_env_node(char **env_arr_tmp)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		exit(1);
	node->env_name = env_arr_tmp[0];
	node->env_content = env_arr_tmp[1];
	node->next = NULL;
	free(env_arr_tmp);
	return (node);
}

void	importing_main_shell_env(char **envp, t_shell *s)
{
	size_t		i;
	t_env		*tmp;
	char		**env_arr_tmp;

	env_arr_tmp = split_with_first_equal_sign(envp[0], s);
	s->envp_list = new_env_node(env_arr_tmp);
	tmp = s->envp_list;
	i = 1;
	while (envp[i])
	{
		env_arr_tmp = split_with_first_equal_sign(envp[i], s);
		tmp->next = new_env_node(env_arr_tmp);
		tmp = tmp->next;
		i++;
	}
}
