/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:51:02 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:51:06 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (c == 0)
			return ((char *)s + ft_strlen(s, '\0'));
		if (*s == '\0')
			return (NULL);
		if (*s++ == (char)c)
			return ((char *)--s);
	}
	return (NULL);
}
