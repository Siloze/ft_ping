/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:22:51 by sajansse          #+#    #+#             */
/*   Updated: 2021/11/04 17:22:53 by sajansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	numb;
	char			charnumb;

	numb = n;
	if (n < 0)
	{
		numb = (unsigned int)(n * -1);
		write(fd, "-", 1);
	}
	if (numb >= 10)
	{
		ft_putnbr_fd(numb / 10, fd);
		charnumb = numb % 10 + 48;
		write(fd, &charnumb, 1);
	}
	else
	{
		charnumb = numb % 10 + 48;
		write(fd, &charnumb, 1);
	}
}
