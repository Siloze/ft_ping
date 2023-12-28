/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:51:13 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:51:16 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void	*temp;

	temp = malloc((ft_strlen(s1, '\0') + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	return (ft_memcpy(temp, (const void *)s1, ft_strlen(s1, '\0') + 1));
}
