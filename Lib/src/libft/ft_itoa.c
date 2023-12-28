/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:47:59 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:48:03 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nb_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	long	nb;
	char	*str;

	size = nb_size(n);
	nb = n;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		*str = '-';
		nb *= -1;
	}
	if (nb == 0)
		*str = '0';
	str[size--] = '\0';
	while (nb && size >= 0)
	{
		str[size] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (str);
}
