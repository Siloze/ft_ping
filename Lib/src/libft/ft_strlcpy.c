/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:51:49 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:51:54 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	if (dstsize > 0)
	{
		while (src[++i] && i < dstsize - 1)
			dst[i] = src[i];
		dst[i] = '\0';
	}	
	return (ft_strlen(src, '\0'));
}
