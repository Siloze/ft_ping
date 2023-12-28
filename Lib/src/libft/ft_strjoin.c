/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:51:29 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 12:11:28 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int clean_s1, int clean_s2)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	s1_len;
	unsigned long	s2_len;
	char			*dst;

	i = -1;
	j = -1;
	s1_len = ft_strlen(s1, '\0');
	s2_len = ft_strlen(s2, '\0');
	dst = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (s1_len)
		while (s1[++i])
			dst[i] = s1[i];
	if (s2_len)
		while (s2[++j])
			dst[s1_len + j] = s2[j];
	dst[s1_len + s2_len] = '\0';
	if (clean_s1)
		free(s1);
	if (clean_s2)
		free(s2);
	return (dst);
}
