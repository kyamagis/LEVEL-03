/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_absolute_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:30:24 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/22 18:34:08 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/make_absolute_path.h"

static void	add_slash_command_to_paths_tail(char **absolute_paths, \
											char *command)
{
	size_t	i;
	char	*tmp;
	char	*slash_command;

	slash_command = my_strjoin("/", command);
	i = 0;
	while (absolute_paths[i])
	{
		tmp = absolute_paths[i];
		absolute_paths[i] = my_strjoin(absolute_paths[i], slash_command);
		free(tmp);
		i++;
	}
	free(slash_command);
}

static char	*search_accessible_absolute_path(char **absolute_paths, \
											char *command)
{
	size_t	i;

	i = 0;
	while (absolute_paths[i] && access(absolute_paths[i], X_OK))
		i++;
	if (absolute_paths[i] != NULL)
		return (my_strdup(absolute_paths[i]));
	g_status = 127;
	i = 0;
	while (absolute_paths[i] && access(absolute_paths[i], F_OK))
		i++;
	if (absolute_paths[i] != NULL)
		strerror_exit(EACCES, absolute_paths[i], 126);
	message_exit(COMMAND_NOT_FOUND, command, 127);
	return (NULL);
}

void	make_absolute_path(t_shell *shell, char **cmd_option)
{
	char	**absolute_paths;
	char	*a_path_command;
	char	*path_content;
	char	**envp;

	if (shell->envp_list == NULL && cmd_option)
		message_exit(COMMAND_NOT_FOUND, cmd_option[0], 127);
	path_content = path_envp_to_str(shell, cmd_option);
	envp = envp_list_to_double_pointer(shell->envp_list, cmd_option);
	if_slash_exists_cmd(envp, cmd_option);
	absolute_paths = my_split(path_content, ':');
	free(path_content);
	add_slash_command_to_paths_tail(absolute_paths, cmd_option[0]);
	a_path_command = search_accessible_absolute_path(absolute_paths, \
													cmd_option[0]);
	execve(a_path_command, cmd_option, envp);
	g_status = FAILURE;
	ft_exit(EXECVE_FAILURE);
}

/*__attribute__((destructor))
static void destructor(void)
{
	system("leaks -q a.out");
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 2)
		return (printf("++++\n"));
	t_env	*envp_list = make_envp_list(envp);
	char **cmd_option = my_split(argv[1], ' ');

	make_absolute_path(envp_list, cmd_option);
}
*/