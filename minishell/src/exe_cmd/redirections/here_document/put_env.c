/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:27:40 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:44:02 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/redirections.h"

static size_t	put_str(char *search_str, \
						t_env *envp_list, int infile_fd, size_t len)
{
	t_env	*tmp;

	tmp = envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->env_name, search_str) == FOUND)
		{
			ft_putstr_fd(tmp->env_content, infile_fd);
			free(search_str);
			return (len + 1);
		}
		tmp = tmp->next;
	}
	free(search_str);
	return (len + 1);
}

static size_t	search_str_from_envp(char *str, \
									t_env *envp_list, int infile_fd)
{
	size_t	len;
	char	*search_str;

	len = 0;
	while (str[len] && str[len] != '\n' && str[len] != ' ')
		len++;
	search_str = my_substr(str, 0, len);
	return (put_str(search_str, envp_list, infile_fd, len));
}

void	put_env(char *str, t_env *envp_list, int infile_fd)
{
	size_t	i;
	char	*exit_status;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				exit_status = ft_itoa(g_status);
				ft_putstr_fd(exit_status, infile_fd);
				free(exit_status);
				i += 2;
			}
			else
				i += search_str_from_envp(&str[i + 1], envp_list, infile_fd);
		}
		ft_putchar_fd(str[i], infile_fd);
		i++;
	}
}

/*int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (0);
	printf("%s\n", argv[0]);
	put_env("1111111$PATH a\n", envp, STDOUT_FILENO);
	put_env("1111111$PATH222222\n", envp, STDOUT_FILENO);
	put_env("$PAT \n\n", envp, STDOUT_FILENO);
	printf("\n");
	exit(0);
}
*/