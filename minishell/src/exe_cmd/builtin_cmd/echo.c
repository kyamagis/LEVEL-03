/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:52:07 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/17 20:17:15 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

static int	find_n_option(char *option)
{
	size_t	i;

	if (option == NULL)
		return (NOT_FOUND);
	if (ft_strncmp(option, "-n", 2) != FOUND)
		return (NOT_FOUND);
	i = 2;
	while (option[i])
	{
		if (option[i] != 'n')
			return (NOT_FOUND);
		i++;
	}
	return (FOUND);
}

static int	find_options(char **echo_cmd_option, size_t *i)
{
	int		hyphen_n_flg;

	hyphen_n_flg = NOT_FOUND;
	if (echo_cmd_option[1] == NULL)
		return (NOT_FOUND);
	while (find_n_option(echo_cmd_option[*i]) == FOUND)
	{
		hyphen_n_flg = FOUND;
		(*i)++;
	}
	return (hyphen_n_flg);
}

void	echo(char **echo_cmd_option)
{
	int		hyphen_n_flg;
	size_t	i;

	i = 1;
	hyphen_n_flg = find_options(echo_cmd_option, &i);
	while (echo_cmd_option[i])
	{
		ft_putstr_fd(echo_cmd_option[i], STDOUT_FILENO);
		if (echo_cmd_option[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (hyphen_n_flg == NOT_FOUND)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_status = SUCCESS;
}

/* int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	char **echo_cmd_option = my_split(argv[1], ' ');
	// size_t i = 0;
	// while (echo_cmd_option[i])
	// {
	// 	ft_putendl_fd(echo_cmd_option[i], STDOUT_FILENO);
	// 	i++;
	// }
	echo(echo_cmd_option);
	exit(EXIT_SUCCESS);
} */
