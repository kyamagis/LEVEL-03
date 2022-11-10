/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamagis <kyamagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:34:30 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/19 17:29:05 by kyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "exe_cmd.h"

# define MALLOC_ERROR_MESSAGE "Malloc error"
# define TOO_MANY_WORDS "Too many words"
# define BUFFER_SIZE 100000
# define MALLOC_ERROR -2
# define READ_ERROR -1
# define NOMAL_END 0
# define CONTINUE  1
# define READ_ERROR_MESSAGE "Read Error"

char			*get_next_line(int fd);
char			*ft_strchr_gnl(char *s, int c);
size_t			ft_strlen_gnl(const char *s);
size_t			ft_strlcpy_gnl(char *dest, char *src, size_t size);
char			*ft_free_str(char *buff, char *saved_str);
char			*my_strdup_gnl(char *s1);

#endif