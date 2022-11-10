/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_shell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:17:19 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 19:45:34 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_SHELL_H
# define LIB_SHELL_H

# include "exe_cmd.h"

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strstr_idx(const char *haystack, const char *needle);
int		ft_isspace(int c);
char	**my_split(char const *s, char c);
char	*my_strdup(const char *s1);
char	*my_strjoin(char const *s1, char const *s2);
char	*my_substr(char const *s, size_t start, size_t len);

#endif