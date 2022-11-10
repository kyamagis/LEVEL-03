/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:07:18 by smuramat          #+#    #+#             */
/*   Updated: 2022/10/24 16:55:37 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**parser(char *cmd_line, t_shell *s)
{
	char	**cmd_arr;

	quote_check(cmd_line, s);
	cmd_line = rm_space(cmd_line, s);
	cmd_line = syntax_check(cmd_line, s);
	save_redirect(cmd_line, s);
	cmd_line = make_new_cmd_without_redirect(cmd_line, s);
	cmd_arr = check_new_line(cmd_line, s);
	cmd_arr = replace_env(cmd_arr, s);
	add_command_to_list(cmd_arr, s);
	rm_quote(s);
	return (cmd_arr);
}

static void	free_after_run_program(t_shell *s)
{
	t_cmd	*tmp;
	size_t	i;

	while (s->cmd)
	{
		tmp = s->cmd->next;
		i = 0;
		while (s->cmd->cmd_option[i])
			free(s->cmd->cmd_option[i++]);
		i = 0;
		free(s->cmd->cmd_option);
		free(s->cmd);
		s->cmd = tmp;
	}
	free_tmp_malloc(s);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_shell	*s;

	s = init(argc, argv, envp);
	while (1)
	{
		cmd = readline("minishell> ");
		if (!cmd)
			free_cmd_and_struct_exit_0(cmd, s);
		add_history(cmd);
		if (cmd[0] != '\0')
		{
			parser(cmd, s);
			exe_cmd(s);
			free_after_run_program(s);
		}
		else
			free(cmd);
	}
}
