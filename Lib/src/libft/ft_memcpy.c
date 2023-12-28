/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:49:57 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:50:01 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{	
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (!src && !dst)
		return (0);
	while (n-- > 0)
		*d++ = *s++;
	return (dst);
}
