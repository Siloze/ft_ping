/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:50:04 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:50:09 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*src2;
	char	*dst2;

	i = -1;
	src2 = (char *)src;
	dst2 = (char *)dst;
	if (!src2 && !dst2)
		return (NULL);
	if (dst <= src)
	{
		while (++i < len)
			dst2[i] = src2[i];
	}
	else
	{
		while (len > 0)
		{
			dst2[len - 1] = src2[len - 1];
			len--;
		}
	}	
	return (dst);
}
