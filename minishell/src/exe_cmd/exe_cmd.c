/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:09:24 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/24 18:08:18 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exe_cmd.h"

void	exe_cmd(t_shell *shell)
{
	g_status = 2;
	shell->here_doc_count = 0;
	if (shell->cmd == NULL)
		return ;
	if (shell->pipe_count == 0 && \
		isbuiltin_cmd(shell->cmd) == FOUND)
		not_pipe_and_builtin_cmd(shell);
	else
		multiple_pipe(shell);
}

/* 
//////////////////////////////////////////////////////////////////

	ft_putstr_fd(ft_itoa((int)g_status), STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);

size_t	*quote_flg(void)
{
	size_t *quote_flg;

	quote_flg = (size_t *)malloc(sizeof(size_t));
	quote_flg[0] = 1;
	return(quote_flg);
}

static t_cmd	*malloc_cmd_line_list(char *argv)
{
	t_cmd	*cmd_line_list;

	cmd_line_list = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd_line_list == NULL)
		ft_exit(MALLOC_FAILURE);
	cmd_line_list->cmd_option = my_split(argv, ' ');
	cmd_line_list->redirections = NULL;//my_split(">end >>en", ' ');
	//cmd_line_list->redirections = my_split("<<end <<end", ' ');
	cmd_line_list->quote_flg = quote_flg();
	cmd_line_list->output_redirection = NOT_FOUND;
	cmd_line_list->pid = 0;
	cmd_line_list->next = NULL;
	return (cmd_line_list);
}

t_cmd	*make_cmd_line_list(char **argv)
{
	t_cmd	*cmd_line_list;
	t_cmd	*tmp;
	size_t		i;

	i = 2;
	cmd_line_list = malloc_cmd_line_list(argv[1]);
	//cmd_line_list->redirections = my_split(">out", ' ');
	//cmd_line_list->redirections = my_split(">>end >END ", ' ');
	tmp = cmd_line_list;
	while (argv[i])
	{
		tmp->next = malloc_cmd_line_list(argv[i]);
		tmp = tmp->next;
		i++;
	}
	//cmd_line_list->redirections = my_split("<end ", ' ');
	//cmd_line_list->redirections = my_split(">a", ' ');
	return (cmd_line_list);
}

__attribute__((destructor))
static void destructor(void)
{
	system("leaks -q exe");
}

int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (printf("invalid argc\n"));

	t_shell	shell;

	ft_putstr_fd("exe_cmd\n", 0);//

	shell.pipe_count = argc - 2;
	shell.file_name_list = NULL;
	shell.envp_list = make_envp_list(envp);
	shell.cmd_line_list = make_cmd_line_list(argv);
	exe_cmd(&shell);
	t_env	*c_pwd = find_env_name_and_return_the_env_pointer(\
						"PWD", &shell);
	t_env	*old_pwd = find_env_name_and_return_the_env_pointer(\
						"OLDPWD", &shell);
	printf("\n\n++++++++++++++++++++++\n");
	if (c_pwd && old_pwd)
		printf("   pwd = %s\noldpwd = %s\n", c_pwd->env_content, \
											old_pwd->env_content);
	printf("g_status = %d\n", g_status);
	exit(EXIT_SUCCESS);

} */
