/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:40 by mbastard          #+#    #+#             */
/*   Updated: 2022/10/19 03:25:49 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;

	if (!src)
		return (NULL);
	dst = (char *)malloc((ft_sublen(src, 0) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_memmove(dst, src, (ft_sublen(src, 0) + 1) * sizeof(char));
	return (dst);
}

char	*ft_strcut(char *src, size_t start, size_t size, int clean)
{
	char	*dst;

	dst = ft_substr(src, 0, start);
	dst = ft_strjoin(dst, &src[start + size], 1, 0);
	if (clean)
		free(src);
	return (dst);
}

char	*ft_substr(const char *src, size_t start, size_t len)
{
	char	*dst;

	if (!src || !len)
		return (NULL);
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_memmove(dst, src + start, len + 1);
	dst[len] = 0;
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2, int clean_s1, int clean_s2)
{
	unsigned long	i;
	unsigned long	s1_len;
	unsigned long	s2_len;
	char			*dst;

	i = -1;
	s1_len = ft_sublen(s1, 0);
	s2_len = ft_sublen(s2, 0);
	if (!s1_len && !s2_len)
		return (NULL);
	dst = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (s1 && ++i < s1_len)
		dst[i] = s1[i];
	while (s2 && ++i < s1_len + s2_len + 1)
		dst[i - 1] = s2[i - s1_len - 1];
	dst[i - 1] = 0;
	if (s1 && clean_s1)
		free(s1);
	if (s2 && clean_s2)
		free(s2);
	return (dst);
}

char	*ft_multijoin(char *clean, ...)
{
	size_t	i;
	char	*dst;
	va_list	arg;

	i = -1;
	dst = NULL;
	va_start(arg, clean);
	while (clean[++i])
		dst = ft_strjoin(dst, va_arg(arg, char *), 1, clean[i] - '0');
	va_end(arg);
	return (dst);
}
