/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:15:47 by mbastard          #+#    #+#             */
/*   Updated: 2022/10/21 19:20:13 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned long	i;

	i = -1;
	while ((dstsize - i) && src[++i] && dst[i])
		dst[i] = src[i];
	dst[i] = 0;
	return (ft_sublen(src, 0));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (dst[i] && dstsize - i)
		i++;
	while ((dstsize - i) && src[j])
		dst[i++] = src[j++];
	dst[i] = 0;
	return (i - j + strlen(src));
}

int	set_search(char const s1, char const *set)
{
	while (*set)
	{
		if (*set++ == s1)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set, int clean)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	start = 0;
	str = NULL;
	if (!s1 || !set)
		return (NULL);
	end = ft_sublen(s1, '\0');
	while (s1[start] && set_search(s1[start], set))
		start++;
	if (start == end)
		return (NULL);
	while (end > start && set_search(s1[end - 1], set))
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	if (clean && s1)
		free(s1);
	return (str);
}
