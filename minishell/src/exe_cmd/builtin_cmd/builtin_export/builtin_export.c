/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:46:39 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:35 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/builtin.h"

static void	put_export_str(t_env	*envp_list)
{
	t_env	*tmp;

	tmp = envp_list;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->env_name, STDOUT_FILENO);
		if (tmp->env_content)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(tmp->env_content, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		tmp = tmp->next;
	}
}

void	builtin_export(t_shell *shell, char **export_cmd_line)
{
	g_status = SUCCESS;
	if (export_cmd_line[1])
		add_export_cmd_line_to_envp(\
			shell, export_cmd_line);
	else
		put_export_str(shell->envp_list);
}

/* 
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 && !argv && !envp)
		return (0);

	char **export_cmd_line = my_split(\
	"export 1 @= abc=abc USER+=ABC PWD XYZ \
				+=MMMMMMMMMMMMM =LLLLLLLLLLLLLLLLL @=", ' ');
	t_env	*envp_list;
	envp_list = make_envp_list(envp);
	export(envp_list, export_cmd_line);

	t_env	*tmp = envp_list;
	t_env	*tmp2;
	printf("++++++++++++++++\n\n");
	while (tmp)
	{
		printf("%s = %s\n", tmp->env_name, tmp->env_content);
		tmp2 = tmp;
		free(tmp->env_name);
		free(tmp->env_content);
		tmp = tmp->next;
		free(tmp2);
	}
	free_double_pointer(export_cmd_line);
	printf("g_status = %d\n", g_status);
	exit(EXIT_SUCCESS);
	return (0);
}
__attribute__((destructor))
static void destructor(void)
{
	system("leaks -q a.out");
} */