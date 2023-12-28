/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:24:55 by sajansse          #+#    #+#             */
/*   Updated: 2021/12/13 15:33:50 by sajansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parametre(va_list *arg, char type, int len)
{		
	if (type == 'c')
		len = ft_putchar(va_arg(*arg, int), len);
	else if (type == 's')
		len = ft_putstr(va_arg(*arg, char *), len);
	else if (type == 'p')
	{
		len = ft_putstr("0x", len);
		len = ft_puthexa(va_arg(*arg, uintptr_t), "0123456789abcdef", len);
	}
	else if (type == 'd' || type == 'i')
		len = ft_putnbr(va_arg(*arg, int), len);
	else if (type == 'u')
		len = ft_putunbr(va_arg(*arg, unsigned int), len);
	else if (type == 'x')
		len = ft_puthexa(va_arg(*arg, unsigned int), "0123456789abcdef", len);
	else if (type == 'X')
		len = ft_puthexa(va_arg(*arg, unsigned int), "0123456789ABCDEF", len);
	else if (type == '%')
		len = ft_putchar('%', len);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int				len;
	int				i;
	va_list			arg;

	len = 0;
	i = -1;
	va_start(arg, format);
	while (format[++i])
	{
		if (format[i] == '%')
			len = ft_parametre(&arg, format[++i], len);
		else
			len = ft_putchar(format[i], len);
	}
	va_end(arg);
	return (len);
}
