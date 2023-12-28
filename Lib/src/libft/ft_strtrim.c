/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:52:30 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:52:33 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	set_search(char const s1, char const *set)
{
	while (*set)
	{
		if (*set++ == s1)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set, int do_free)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1, '\0');
	while (s1[start] && set_search(s1[start], set))
		start++;
	while (end > start && set_search(s1[end - 1], set))
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	if (do_free)
		free ((char *)s1);
	return (str);
}
