/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:45:21 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/19 16:11:38 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../includes/gnl.h"

static char	*dup_nl_to_null(char *saved_str)
{
	size_t		nl_point;
	char		*tmp_str;

	nl_point = 0;
	while (saved_str[nl_point] != '\0' && saved_str[nl_point] != '\n')
		nl_point++;
	if (saved_str[nl_point] == '\n')
		nl_point++;
	tmp_str = my_strdup_gnl(&saved_str[nl_point]);
	ft_free_str(NULL, saved_str);
	if (tmp_str == NULL)
		return (NULL);
	saved_str = tmp_str;
	return (saved_str);
}

static char	*dup_to_nl(char *saved_str)
{
	char	*output_line;
	size_t	nl_point;

	nl_point = 0;
	while (saved_str[nl_point] != '\0' && saved_str[nl_point] != '\n')
		nl_point++;
	if (saved_str[nl_point] == '\n')
		nl_point++;
	output_line = (char *)malloc (sizeof(char) * (nl_point + 1));
	if (output_line == NULL)
		return (NULL);
	ft_strlcpy_gnl(output_line, saved_str, nl_point + 1);
	return (output_line);
}

static char	*ft_join_to_null(char	*saved_str, char *buff)
{
	char	*joined;
	size_t	len_sv;
	size_t	len_bf;

	len_sv = ft_strlen(saved_str);
	len_bf = ft_strlen(buff);
	joined = (char *)malloc(sizeof(char) * (len_sv + len_bf + 1));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy_gnl(joined, saved_str, len_sv + 1);
	ft_strlcpy_gnl(&joined[len_sv], buff, len_bf + 1);
	return (joined);
}

static char	*read_to_null(int fd, char *saved_str)
{
	ssize_t	readsz;
	char	*buff;
	char	*tmp_str;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1UL));
	if (buff == NULL)
		return (NULL);
	readsz = 1;
	while (0 < readsz && ft_strchr_gnl(saved_str, '\n') == NULL)
	{
		readsz = read(fd, buff, BUFFER_SIZE);
		if (readsz == -1 || (readsz == 0 && saved_str[0] == '\0'))
			return (ft_free_str(buff, saved_str));
		buff[readsz] = '\0';
		tmp_str = ft_join_to_null(saved_str, buff);
		if (tmp_str == NULL)
			return (ft_free_str(buff, saved_str));
		ft_free_str(NULL, saved_str);
		saved_str = tmp_str;
	}
	ft_free_str(buff, NULL);
	return (saved_str);
}

char	*get_next_line(int fd)
{
	static char	*saved_str;
	char		*output_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (saved_str == NULL)
	{
		saved_str = ft_strdup("");
		if (saved_str == NULL)
			return (NULL);
	}
	saved_str = read_to_null(fd, saved_str);
	if (saved_str == NULL)
		return (NULL);
	output_line = dup_to_nl(saved_str);
	if (output_line == NULL)
		return (ft_free_str(NULL, saved_str));
	saved_str = dup_nl_to_null(saved_str);
	if (saved_str == NULL)
		return (ft_free_str(output_line, NULL));
	return (output_line);
}

/*int	main(void)
{
	int		fd;
	char	*lineBf;

	fd = open("test", O_RDONLY , 0);
	if (fd < 0)
	{
		printf("!!! ERROR 1 !!!\n");
	}
	while (1)
	{
		lineBf = get_next_line(fd);
		
		
		if (lineBf == NULL)
		{
			printf("EOF\n");
			break;
		}
		printf("%s", lineBf);
	}

	printf("+++++++++++++++++++++++++++++++++++++++++\n");

	int		fd;
	char	*lineBf;

	fd = open("empty", O_RDONLY , 0);
	if (fd < 0)
	{
		printf("!!! ERROR 1 !!!\n");
	}
	while (1)
	{
		lineBf = get_next_line(fd);
		
		
		if (lineBf == NULL)
		{
			printf("EOF\n");
			break;
		}
		printf("%s", lineBf);
	}

	printf("+++++++++++++++++++++++++++++++++++++++++\n");
	
	fd = open("test", O_RDONLY , 0);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		readsz = read(fd, buff, BUFFER_SIZE);
	printf("%zd\n", readsz);
	buff[readsz] = '\0';
	printf("%s\n", buff);
	
	printf("check_read_+++++++++++++++++++++++++++++++++++++++++\n");

	printf("%s\n", ft_join_to_null(my_strdup(""), "GUNDUM"));
	printf("%s\n", ft_join_to_null("Z_", "GUNDUM"));
	int		fd;
	char	*lineBf;

	fd = open("empty", O_RDONLY , 0);
	if (fd < 0)
		printf("!!! ERROR 1 !!!\n");
	lineBf = read_to_null(fd, my_strdup(""));
	printf("%s\n", lineBf);

	printf("+++++++++++++++++++++++++++++++++++++++++\n");

	int		fd;
	char	*lineBf;

	fd = open("test.txt", O_RDONLY , 0);
	if (fd < 0)
	{
		printf("!!! ERROR 1 !!!\n");
	}
	
		lineBf = get_next_line(fd);
		printf("%s", lineBf);
		lineBf = get_next_line(fd);
		printf("%s", lineBf);
		lineBf = get_next_line(fd);
		printf("%s", lineBf);
		

	int		fd;
	char	*lineBf;
	char	*lineBf1;

	fd = open("test.txt", O_RDONLY , 0);
	lineBf = get_next_line(fd);
	printf("%s", lineBf);
	
	lineBf1 = read_to_null(fd, NULL);
	printf("%s", lineBf1);
	


	int		fd;
	char	*lineBf;
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;
	char	*str5;
	size_t nl_point;

	nl_point = 0;
	fd = open("test.txt", O_RDONLY , 0);
	if (fd < 0)
	{
		printf("!!! ERROR 1 !!!\n");
		exit(1);
	}
	
		lineBf = read_to_null(fd, NULL);
		if (lineBf == NULL)
		{
			printf("EOF\n");
		}
		printf("%s\n", lineBf);
	str1= my_strdup("get");
	str2= my_strdup("_wild");
	str3= my_strdup("\nabc");
	str4= my_strdup("ab\n\nb");
	str5= my_strdup("a\nb");
	
	printf("\\nabc %s\n", ft_dup_to_nl(str3));
	printf("ab\\n %s\n", ft_dup_to_nl(str4));
	printf("a\\nb %s\n", ft_dup_to_nl(str5));
	

	printf("%s\n", ft_join_to_null(NULL, "abxd"));
	printf("%s\n", ft_join_to_null(str1, str2));

	printf("\\nabc %s\n", dup_to_null(str3));
	printf("ab\\n %s\n", dup_to_null(str4));
	printf("a\\nb %s\n", dup_to_null(str5));
}*/
