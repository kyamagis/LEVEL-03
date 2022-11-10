/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalnum_underscore_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:22:47 by kyamagis          #+#    #+#             */
/*   Updated: 2022/10/14 20:46:20 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/builtin.h"

int	isalnum_underscore_str(char *str)
{
	size_t	i;

	if (!str || ft_isdigit(str[0]))
	{
		g_status = FAILURE;
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (!isalnum_underscore(str[i]))
		{	
			g_status = FAILURE;
			return (0);
		}
		i++;
	}
	return (1);
}
