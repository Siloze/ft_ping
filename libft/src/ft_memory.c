/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:17 by mbastard          #+#    #+#             */
/*   Updated: 2022/09/15 05:05:33 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	while (n--)
		((unsigned char *)ptr)[n] = 0;
}

void	ft_memset(void *ptr, int val, size_t n)
{
	while (n--)
		((unsigned char *)ptr)[n] = (char)val;
}

void	ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (dst && src && dst > src)
		while (n--)
			((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	if (dst && src && dst < src)
		while (++i < n)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*mem;
	size_t	len;

	len = n * size;
	mem = malloc(len);
	if (!mem)
		return (NULL);
	while (len--)
		((unsigned char *)mem)[len] = 0;
	return (mem);
}

void	*ft_realloc(void *ptr, size_t n, size_t size)
{
	void	*mem;
	size_t	len;
	size_t	i;

	i = -1;
	len = n * size;
	mem = malloc(len);
	if (!mem)
		return (NULL);
	if (ptr && mem > ptr)
		while (len--)
			((unsigned char *)mem)[len] = ((unsigned char *)ptr)[len];
	if (ptr && mem < ptr)
		while (++i < len)
			((unsigned char *)mem)[i] = ((unsigned char *)ptr)[i];
	if (ptr)
		free(ptr);
	return (mem);
}
