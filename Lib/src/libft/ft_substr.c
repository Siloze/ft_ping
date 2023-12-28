/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:52:37 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:52:41 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, int do_free)
{
	char			*str;
	unsigned int	i;
	unsigned int	k;

	i = -1;
	k = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[++i])
	{
		if (i >= start && k < len)
			str[k++] = s[i];
	}
	str[k] = '\0';
	if (do_free)
		free ((char *)s);
	return (str);
}
