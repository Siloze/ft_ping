/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:38:26 by mbastard          #+#    #+#             */
/*   Updated: 2022/08/07 22:33:13 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putsub_fd(int fd, const char *str, char c)
{
	write(fd, str, ft_sublen(str, c));
}

void	ft_putnbr_fd(int fd, int nbr)
{
	if (nbr == -2147483648)
		ft_putsub_fd(fd, "-2147483648", 0);
	else
	{
		if (nbr < 0)
		{
			nbr *= -1;
			ft_putchar_fd(fd, '-');
		}
		if (nbr >= 10)
			ft_putnbr_fd(fd, nbr / 10);
		write(fd, &"0123456789"[nbr % 10], 1);
	}
}

void	ft_putunbr_fd(int fd, size_t nbr)
{
	if (nbr >= 10)
		ft_putunbr_fd(fd, nbr / 10);
	write(fd, &"0123456789"[nbr % 10], 1);
}

void	ft_putunbrbase_fd(int fd, size_t nbr, const char *base)
{
	if (nbr >= ft_sublen(base, 0))
		ft_putunbrbase_fd(fd, nbr / ft_sublen(base, 0), base);
	write(fd, &base[nbr % ft_sublen(base, 0)], 1);
}
