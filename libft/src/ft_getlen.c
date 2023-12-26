/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:31 by mbastard          #+#    #+#             */
/*   Updated: 2022/08/07 22:32:47 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_sublen(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str && str[len] != c && str[len])
		len++;
	return (len);
}

size_t	ft_tablen(char **tab, const char *str)
{
	size_t	len;

	len = 0;
	while (tab && tab[len] && ft_strncmp(tab[len], str, ft_sublen(str, 0)))
		len++;
	return (len);
}

size_t	ft_nbrlen(int nbr)
{
	size_t	len;

	len = 1;
	if (nbr == -2147483648)
		nbr++;
	if (nbr < 0 && ++len)
		nbr *= -1;
	while (nbr > 9 && ++len)
		nbr = nbr / 10;
	return (len);
}

size_t	ft_unbrlen(size_t nbr)
{
	size_t	len;

	len = 1;
	while (nbr > 9 && ++len)
		nbr = nbr / 10;
	return (len);
}
