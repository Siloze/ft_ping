/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:51:57 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:52:00 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s, char c)
{
	int	len;

	len = -1;
	if (s)
	{
		while (s[++len] != c)
			;
	}
	return (len);
}

int	ft_strlen_start(const char *s, int start, char c)
{
	int	len;

	len = 0;
	if (s)
	{
		while (s[start] != c)
		{
			start++;
			len++;
		}
	}
	return (len);
}
