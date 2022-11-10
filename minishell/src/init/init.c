/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:40:53 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/22 21:27:36 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	g_status;

void static	init_check(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		printf("Usage: ./minishell");
		exit(1);
	}
}

void	sigfunc2(int signum)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(signum, 2);
	ft_putstr_fd("\n", 2);
	g_status = 131;
}

t_shell	*init(int argc, char **argv, char **envp)
{
	t_shell	*s;

	g_status = 0;
	init_check(argc, argv);
	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
		status_on_and_exit(s);
	s->file_name_list = NULL;
	signal(SIGINT, sigfunc);
	signal(SIGQUIT, SIG_IGN);
	if (envp && envp[0])
		importing_main_shell_env(envp, s);
	else
		s->envp_list = NULL;
	return (s);
}
