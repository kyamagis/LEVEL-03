/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:28:52 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/17 15:03:23 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

static void	find_env_name_and_rewrite_env_content(\
		t_shell *shell, char *env_name, char *env_content)
{
	t_env	*envp_list;

	envp_list = find_env_name_and_return_the_env_pointer(\
				env_name, shell);
	if (envp_list == NULL)
		return ;
	free(envp_list->env_content);
	envp_list->env_content = my_strdup(env_content);
}

static void	cd_error_handling(char *cd_arg, char *old_pwd, int home_flg)
{
	g_status = FAILURE;
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (home_flg == FOUND)
		ft_putendl_fd("HOME not set", STDERR_FILENO);
	else
	{
		if (cd_arg)
			strerror_file_name(errno, cd_arg, 1);
	}
	if (old_pwd)
		free(old_pwd);
}

static void	set_current_pwd_old_pwd(\
		t_shell *shell, char *old_pwd)
{
	char	*current_pwd;

	find_env_name_and_rewrite_env_content(shell, "OLDPWD", old_pwd);
	free(old_pwd);
	current_pwd = getcwd(NULL, 0);
	find_env_name_and_rewrite_env_content(shell, "PWD", current_pwd);
	free(current_pwd);
}

static void	home_directory(t_shell *shell)
{
	t_env	*home_envp;
	char	*old_pwd;

	home_envp = find_env_name_and_return_the_env_pointer("HOME", shell);
	if (home_envp->env_content == NULL || home_envp->env_content[0] == '\0')
	{	
		cd_error_handling(NULL, NULL, FOUND);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(home_envp->env_content) == -1)
	{
		cd_error_handling(NULL, old_pwd, NOT_FOUND);
		return ;
	}
	set_current_pwd_old_pwd(shell, old_pwd);
}

void	cd(char **cmd_option, t_shell *shell)
{
	char	*old_pwd;

	g_status = SUCCESS;
	if (cmd_option[1] == NULL)
	{	
		home_directory(shell);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(cmd_option[1]) == -1)
	{
		cd_error_handling(cmd_option[1], old_pwd, NOT_FOUND);
		return ;
	}
	set_current_pwd_old_pwd(shell, old_pwd);
}
/* 
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	g_status = SUCCESS;
	char **cd_arg = my_split(argv[1], ' ');
	t_shell	shell;
	shell.envp_list = make_envp_list(envp);
	cd(cd_arg, &shell);
	t_env	*c_pwd = find_env_name_and_return_the_env_pointer(\
						"PWD", &shell);
	t_env	*old_pwd = find_env_name_and_return_the_env_pointer(\
						"OLDPWD", &shell);

	printf("   pwd = %s\noldpwd = %s\n", c_pwd->env_content, old_pwd->env_content);
	printf("g_status = %d\n", g_status);
	pwd();
	exit(0);

} */