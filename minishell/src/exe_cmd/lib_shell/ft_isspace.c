/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:18:22 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:44:54 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lib_shell.h"

int	ft_isspace(int c)
{
	return ((c == ' ') || (c == '\f') || (c == '\n') \
	|| (c == '\r') || (c == '\t') || (c == '\v'));
}
