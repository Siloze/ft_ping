/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajansse <sajansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:32:09 by sajansse          #+#    #+#             */
/*   Updated: 2022/01/21 04:03:58 by sajansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);

int	ft_putchar(char c, int size);
int	ft_putstr(char *s, int size);
int	ft_putnbr(int n, int size);
int	ft_putunbr(unsigned int n, int size);
int	ft_puthexa(unsigned long n, char *base, int size);

#endif
