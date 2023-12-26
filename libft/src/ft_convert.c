/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:26:33 by mbastard          #+#    #+#             */
/*   Updated: 2022/09/15 21:05:41 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	if (ft_strchr("-+0123456789", *str, 0))
	{
		if (*str == 45)
			sign = -1;
		if (ft_isdigit(*str))
			result = result * 10 + (*str - 48);
		while (ft_isdigit(*++str))
			result = result * 10 + (*str - 48);
	}
	return (result * sign);
}

char	*ft_itoa(int nbr)
{
	size_t	len;
	char	*str;

	len = ft_nbrlen(nbr);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (nbr == -2147483648)
	{
		str[10] = '8';
		nbr = -214748364;
	}
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (len-- && str[len] != '-')
	{
		str[len] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (str);
}

char	**ft_split(const char *str, char c)
{
	unsigned long	i;
	unsigned long	div;
	char			**tab;

	i = -1;
	div = 1;
	if (!str)
		return (NULL);
	while (str[++i])
		if (str[i] == c && str[i + 1] != c && str[i + 1])
			div++;
	tab = (char **)ft_calloc(div + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = -1;
	div = -1;
	while (str[++i])
		if (str[i] != c && (str[i - 1] == c || !i))
			tab[++div] = ft_substr(str, i, ft_sublen(&str[i], c));
	tab[++div] = NULL;
	return (tab);
}
