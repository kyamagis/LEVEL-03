/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_unique_file_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:08:56 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:43:50 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/redirections.h"

static char	*join_str_and_chr(char const *s1, char const s2)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;

	lens1 = ft_strlen(s1);
	lens2 = 1;
	str = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (str == NULL)
		ft_exit(MALLOC_FAILURE);
	ft_strlcpy(str, s1, lens1 + 1);
	str[lens1] = s2;
	str[lens1 + lens2] = '\0';
	return (str);
}

static int	alfabet_joiun(char **unique_file_name, char *tmp_name)
{
	size_t	i;

	i = 0;
	while (i < 'z' - 'a')
	{
		*unique_file_name = join_str_and_chr(tmp_name, 'a' + i);
		if (access(*unique_file_name, F_OK) != ACCESSIBLE)
			return (ACCESSIBLE);
		free (*unique_file_name);
		i++;
	}
	return (1);
}

char	*create_unique_file_name(char *file_name)
{
	char	*unique_file_name;
	char	*tmp_name;
	int		flag;

	if (file_name == NULL)
		ft_exit("file_name_is_NULL");
	if (access(file_name, F_OK) != ACCESSIBLE)
		return (my_strdup(file_name));
	unique_file_name = my_strdup(file_name);
	flag = 1;
	while (flag != ACCESSIBLE)
	{
		tmp_name = unique_file_name;
		flag = alfabet_joiun(&unique_file_name, tmp_name);
		free (tmp_name);
	}
	return (unique_file_name);
}

/*__attribute__((destructor))
static void destructor(void)
{
	system("leaks -q a.out");
}

int main(void)
{
	char *s1 = "a";
	char *s3 = create_unique_file_name(s1);
	printf("%s\n", s3);
	free(s3);
}
*/