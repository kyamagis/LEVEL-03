/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_export_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:09:20 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:38 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/builtin.h"

static char	*export_substr(char const *s, size_t start, size_t len)
{
	char	*substr;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	if (len == SIZE_MAX)
		return (NULL);
	substr = (char *)malloc (sizeof (char) * (len + 1));
	if (substr == NULL)
		ft_exit(MALLOC_FAILURE);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}

static t_env	*malloc_export_list_and_assignment(\
		char *export_cmd_line, size_t equal_idx, int plus_flg)
{
	t_env	*export_list;

	export_list = (t_env *)malloc(sizeof(t_env));
	if (export_list == NULL)
	{	
		g_status = FAILURE;
		exit(EXIT_FAILURE);
	}
	export_list->env_name = NULL;
	export_list->env_content = export_substr(\
		export_cmd_line + equal_idx + 1, \
		0, ft_strlen(export_cmd_line));
	export_list->plus_flg = plus_flg;
	if (export_list->env_content == NULL && plus_flg == 0)
		export_list->env_content = my_strdup("");
	export_list->next = NULL;
	return (export_list);
}

static size_t	serch_equal_idx_and_set_plus_flg(int *plus_flg, \
									char *export_cmd_line)
{
	size_t	equal_idx;

	equal_idx = ft_strstr_idx(export_cmd_line, "=");
	*plus_flg = -1;
	if (export_cmd_line[equal_idx] == '=')
		*plus_flg = 0;
	if (0 < equal_idx && export_cmd_line[equal_idx - 1] == '+')
		*plus_flg = 1;
	return (equal_idx);
}

static t_env	*dup_cmdline_to_list(char *export_cmd_line)
{
	size_t	equal_idx;
	t_env	*export_list;
	int		plus_flg;
	char	*env_name;

	plus_flg = 0;
	equal_idx = serch_equal_idx_and_set_plus_flg(&plus_flg, \
									export_cmd_line);
	env_name = my_substr(export_cmd_line, 0, equal_idx - plus_flg);
	if (env_name == NULL || env_name[0] == '\0' || \
		!isalnum_underscore_str(env_name))
	{
		builtin_puterror("export:", export_cmd_line);
		free(env_name);
		return (NULL);
	}
	export_list = malloc_export_list_and_assignment(\
					export_cmd_line, equal_idx, plus_flg);
	export_list->env_name = env_name;
	return (export_list);
}

t_env	*make_export_list(char **export_cmd_line)
{
	t_env	*export_list;
	t_env	*tmp;
	size_t	i;

	i = 1;
	export_list = NULL;
	while (export_list == NULL && export_cmd_line[i])
	{
		export_list = dup_cmdline_to_list(export_cmd_line[i]);
		i++;
	}
	tmp = export_list;
	while (export_cmd_line[i])
	{
		tmp->next = dup_cmdline_to_list(export_cmd_line[i]);
		if (tmp->next)
			tmp = tmp->next;
		i++;
	}
	return (export_list);
}

/* int	main(int argc, char **argv)
{
	if (argc != 1 && !argv)
		return (0);
	char **export_cmd_line = my_split("abc=abc abc+=ABC abc", ' ');
	t_env	*export_list = make_export_list(export_cmd_line);
	t_env	*tmp = export_list;
	t_env	*tmp2;
	while (tmp)
	{
		printf("%s, %s, %d\n", tmp->envp, tmp->env_content, tmp->plus_flg);
		free(tmp->envp);
		free(tmp->env_content);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	exit(EXIT_SUCCESS);
} */
