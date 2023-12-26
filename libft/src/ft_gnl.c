/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:24:26 by mbastard          #+#    #+#             */
/*   Updated: 2022/09/15 23:16:08 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_mini_gnl(int fd)
{
	char	*line;
	char	buff[2];

	line = NULL;
	if (fd < 0 || read(fd, buff, 0) < 0)
		return (NULL);
	buff[read(fd, buff, 1)] = 0;
	line = ft_strjoin(line, buff, 1, 0);
	while (ft_sublen(buff, 0) && buff[0] != '\n')
	{
		buff[read(fd, buff, 1)] = 0;
		if (ft_sublen(buff, 0) && buff[0] != '\n')
			line = ft_strjoin(line, buff, 1, 0);
	}
	return (line);
}

char	**ft_read_file(int fd)
{
	char	**map;
	char	*line;
	char	*mem;

	mem = NULL;
	line = ft_mini_gnl(fd);
	if (!line)
		exit(0);
	mem = ft_strjoin(mem, line, 1, 1);
	while (line)
	{
		line = ft_mini_gnl(fd);
		mem = ft_strjoin(mem, line, 1, 1);
	}
	map = ft_split(mem, '\n');
	return (map);
}
