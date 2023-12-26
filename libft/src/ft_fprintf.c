/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:24:26 by mbastard          #+#    #+#             */
/*   Updated: 2022/10/10 16:16:14 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * @brief 	convert and print argument (arg) to the output (fd) according to the
 *			type identifier (id)
 *
 * @param fd 	file descriptor
 * @param id 	type identifier
 * @param arg 	argument to print
 */
static void	ft_put_fd(int fd, char id, va_list *arg)
{
	if (id == 'c')
		ft_putchar_fd(fd, va_arg(*arg, int));
	else if (id == 's')
		ft_putsub_fd(fd, va_arg(*arg, char *), 0);
	else if (id == 'p')
	{
		ft_putsub_fd(fd, "0x", 0);
		ft_putunbrbase_fd(fd, va_arg(*arg, size_t), "0123456789abcdef");
	}
	else if (id == 'd' || id == 'i')
		ft_putnbr_fd(fd, va_arg(*arg, int));
	else if (id == 'u')
		ft_putunbr_fd(fd, va_arg(*arg, size_t));
	else if (id == 'x')
		ft_putunbrbase_fd(fd, va_arg(*arg, size_t), "0123456789abcdef");
	else if (id == 'X')
		ft_putunbrbase_fd(fd, va_arg(*arg, size_t), "0123456789ABCDEF");
	else
	{
		ft_putchar_fd(fd, '%');
		if (id != '%')
			ft_putchar_fd(fd, id);
	}
}

void	ft_fprintf(int fd, const char *format, ...)
{
	va_list			arg;

	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
			ft_put_fd(fd, *++format, &arg);
		else
			ft_putchar_fd(fd, *format);
		format++;
	}
	va_end(arg);
}
