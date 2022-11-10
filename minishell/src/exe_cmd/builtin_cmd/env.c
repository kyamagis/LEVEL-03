/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:51:53 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/17 11:59:29 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

void	env(char **cmd_option, t_env *envp_list)
{
	t_env	*tmp;

	if (cmd_option[1])
	{	
		ft_putstr_fd("env :", STDOUT_FILENO);
		strerror_file_name(ENOENT, cmd_option[1], 127);
		return ;
	}
	tmp = envp_list;
	while (tmp)
	{
		if (tmp->env_content)
		{
			ft_putstr_fd(tmp->env_name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(tmp->env_content, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	g_status = SUCCESS;
}

/*
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 && !argv)
		return (0);

	t_env	*envp_list;
	envp_list = make_envp_list(envp);
	env(envp_list);
	exit(EXIT_SUCCESS);
}

__attribute__((destructor))
static void destructor(void)
{
	system("leaks -q a.out");
}
*/
