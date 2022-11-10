/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminate_accessible_file.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:00:45 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:43:14 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/redirections.h"

int	discriminate_accessible_infile(char *infile_name)
{
	int	fd;

	fd = open(infile_name, O_DIRECTORY);
	close(fd);
	if (fd != -1)
		return (strerror_file_name(EISDIR, infile_name, 1));
	if (access(infile_name, F_OK) == ACCESSIBLE && \
		access(infile_name, R_OK) == ACCESSIBLE)
		return (1);
	g_status = FAILURE;
	if (access(infile_name, F_OK) == ACCESSIBLE)
		return (strerror_file_name(EACCES, infile_name, 1));
	else
		return (strerror_file_name(ENOENT, infile_name, 1));
}

int	discriminate_accessible_outfile(char *outfile_name)
{
	int	fd;

	fd = open(outfile_name, O_DIRECTORY);
	close(fd);
	if (fd != -1)
		return (strerror_file_name(EISDIR, outfile_name, 1));
	if (access(outfile_name, F_OK) == ACCESSIBLE && \
		access(outfile_name, W_OK) == ACCESSIBLE)
		return (1);
	if (access(outfile_name, F_OK) == ACCESSIBLE)
	{
		g_status = FAILURE;
		return (strerror_file_name(EACCES, outfile_name, 1));
	}
	return (1);
}

/*


__attribute__((destructor))
static void destructor(void)
{
	system("leaks -q pipex");
}

void	print_double_pointer(char **envp)
{
	size_t	i = 0;

	while(envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}*/
