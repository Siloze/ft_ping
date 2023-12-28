/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samueljanssens <samueljanssens@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:52:19 by hvincent          #+#    #+#             */
/*   Updated: 2022/04/08 22:36:16 by samueljanss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	k;

	i = -1;
	k = 0;
	while (needle[k])
		k++;
	if (!k)
		return ((char *)haystack);
	while ((haystack[++i]) && i < len)
	{
		if (k <= len - i)
		{
			if (ft_strncmp(&haystack[i], needle, k) == 0)
				return ((char *)&haystack[i]);
		}
	}
	return (0);
}
