/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:04:36 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/24 16:55:59 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/redirections.h"

static void	write_to_infile(t_shell *shell, \
							int infile_fd, char *end_str, size_t quote_flg)
{
	char	*str;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (str == NULL || g_status == 1000)
			break ;
		if (!ft_strncmp(str, end_str, ft_strlen(end_str)) && \
			str[ft_strlen(end_str)] == '\n')
			break ;
		if (quote_flg == 1)
			put_env(str, shell->envp_list, infile_fd);
		else
			ft_putstr_fd(str, infile_fd);
		free(str);
		str = NULL;
	}
	free(str);
}

static int	create_infile_and_write(t_shell *shell, \
									char *end_str, \
									size_t quote_flg, \
									t_file_name_list *tail)
{
	int	infile_fd;
	int	tmp_fd;

	infile_fd = open(tail->file_name, O_CREAT | O_RDWR | O_TRUNC, \
					ONLY_WRITE_PERMISSION);
	if (infile_fd == -1)
		ft_exit(OPEN_FAILURE);
	tmp_fd = dup(STDIN_FILENO);
	signal(SIGINT, sig_heredoc_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	write_to_infile(shell, infile_fd, end_str, quote_flg);
	close(infile_fd);
	signal(SIGINT, sigfunc);
	if (g_status == 1000)
	{	
		g_status = 1000;
		dup2(tmp_fd, STDIN_FILENO);
		close(tmp_fd);
		return (-1);
	}
	close(tmp_fd);
	return (1);
}

int	here_document(t_shell *shell, \
					char *end_str, \
					size_t quote_flg, \
					int *pipefd)
{
	int					infile_fd;
	t_file_name_list	*tail;

	g_status = 0;
	shell->here_doc_count += 1;
	tail = find_list_tail(shell);
	if (1 < shell->here_doc_count)
		delete_created_a_file(tail);
	tail->file_name = create_unique_file_name(".here_doc");
	if (create_infile_and_write(shell, end_str, quote_flg, tail) == -1)
		return (-1);
	infile_fd = open(tail->file_name, O_RDONLY);
	if (infile_fd == -1)
		ft_exit(OPEN_FAILURE);
	if (pipefd[READ] != STDIN_FILENO)
		close(pipefd[READ]);
	pipefd[READ] = infile_fd;
	return (1);
}
