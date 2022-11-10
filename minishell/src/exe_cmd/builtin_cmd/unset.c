/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:08:36 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:04 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

static t_env	*delete_first_env(\
					char *option, t_shell *shell)
{
	t_env	*next;

	while (shell->envp_list && \
			ft_strcmp(option, shell->envp_list->env_name) == FOUND)
	{
		next = shell->envp_list->next;
		free(shell->envp_list->env_name);
		free(shell->envp_list->env_content);
		free(shell->envp_list);
		shell->envp_list = next;
	}
	return (shell->envp_list);
}

static void	delete_a_envp(char *option, t_shell *shell)
{
	t_env	*tmp;
	t_env	*prev;

	delete_first_env(option, shell);
	if (shell->envp_list == NULL)
		return ;
	prev = shell->envp_list;
	tmp = shell->envp_list->next;
	while (tmp)
	{
		if (ft_strcmp(option, tmp->env_name) == FOUND)
		{
			prev->next = tmp->next;
			free(tmp->env_name);
			free(tmp->env_content);
			free(tmp);
			tmp = prev->next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	unset(char **cmd_option, t_shell *shell)
{
	size_t	i;

	g_status = SUCCESS;
	if (shell->envp_list == NULL || \
		shell->envp_list->env_name == NULL)
		return ;
	i = 1;
	while (cmd_option[i])
	{
		if (!isalnum_underscore_str(cmd_option[i]))
			builtin_puterror("unset:", cmd_option[i]);
		else
			delete_a_envp(cmd_option[i], shell);
		i++;
	}
}

/* __attribute__((destructor))
static void destructor(void)
{
	system("leaks -q a.out");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	
	t_shell	shell;

	shell.envp_list = make_envp_list(envp);
	char **unset_str = my_split(argv[1], ' ');
	unset(unset_str, &shell);
	t_env	*tmp = shell.envp_list;
	while (tmp)
	{
		printf("%s = %s\n", tmp->env_name, tmp->env_content);
		tmp = tmp->next;
	}
	printf("status = %d\n", g_status);
	exit(0);
	
} */