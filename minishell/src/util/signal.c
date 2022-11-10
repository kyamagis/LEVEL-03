/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:23:31 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/24 18:08:58 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_heredoc_ctrl_c(int signum)
{
	(void)signum;
	g_status = 1000;
	close(STDIN_FILENO);
	printf ("\n");
}	

void	sigfunc(int signum)
{
	(void)signum;
	printf ("\n");
	if (g_status == 2)
		g_status = 130;
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}
