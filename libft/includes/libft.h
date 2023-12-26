/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:06:08 by mbastard          #+#    #+#             */
/*   Updated: 2022/10/17 16:58:07 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_lst {
	struct s_lst	*previous;
	void			*content;
	struct s_lst	*next;
}					t_lst;

//		ft_char_class.c functions

/**
 * @brief 	check if the character (c) is a 7-bit US-ASCII character code
 *
 * @param c character to check
 * @return 	1 or 0
 */
int		ft_isascii(int c);
/**
 * @brief 	check if the character (c) is a printable character
 *
 * @param c character to check
 * @return 	1 or 0
 */
int		ft_isprint(int c);
/**
 * @brief 	check if the character (c) is an alphanumeric character
 *
 * @param c character to check
 * @return 	1 or 0
 */
int		ft_isalnum(int c);
/**
 * @brief 	check if the character (c) is an alphabetic character
 *
 * @param c character to check
 * @return 	1 or 0
 */
int		ft_isalpha(int c);
/**
 * @brief 	check if the character (c) is a numeric character
 *
 * @param c character to check
 * @return 	1 or 0
 */
int		ft_isdigit(int c);

//		ft_convert.c functions

/**
 * @brief 	converts the string (str) to an integer
 *
 * @param str 	string to convert
 * @return 		str converted to an integer
 */
int		ft_atoi(const char *str);
/**
 * @brief 	convert the number (nbr) to a string
 *
 * @param nbr 	number to convert
 * @return 		nbr converted to a string
 */
char	*ft_itoa(int nbr);
/**
 * @brief 	convert the string (str) to a table of strings separed by the
 *			character (c)
 *
 * @param str 	string to split
 * @param c 	separation character
 * @return 		table of string
 */
char	**ft_split(const char *str, char c);

//		ft_fprintf.c function

/**
 * @brief 	prints to the output (fd) the string (format) that specifies how
 *			subsequent arguments are converted for output
 *
 * @param fd 		file descriptor
 * @param format 	string
 * @param ... 		arguments to print
 */
void	ft_fprintf(int fd, const char *format, ...);

//		ft_getlen.c functions

/**
 * @brief 	calculates the length of the (c) character-terminated string (str)
 *
 * @param str 	string
 * @param c 	end character
 * @return 		length of the c-terminated string
 */
size_t	ft_sublen(const char *str, char c);
/**
 * @brief 	calculates the length of the (str) string-terminated table (tab)
 *
 * @param tab 	table
 * @param str 	end string
 * @return 		length of the str-terminated table
 */
size_t	ft_tablen(char **tab, const char *str);
/**
 * @brief 	calculates the length of the alphabetical representation of the
 *			number (nbr)
 *
 * @param nbr 	number
 * @return 		length of the alphabetical representation of nbr
 */
size_t	ft_nbrlen(int nbr);
/**
 * @brief 	calculates the length of the alphabetical representation of the
 *			unsigned number (nbr)
 *
 * @param nbr 	unsigned number
 * @return 		length of the alphabetical representation of nbr
 */
size_t	ft_unbrlen(size_t nbr);

//		ft_gnl.c functions

/**
 * @brief 	return the next line in the input (fd)
 *
 * @param fd 	file descriptor
 * @return 		the next line
 */
char	*ft_mini_gnl(int fd);
/**
 * @brief 	read file in input (fd)
 *
 * @param fd	file descriptor
 * @return 	file's text
 */
char	**ft_read_file(int fd);

//		ft_lst.c functions

t_lst	*ft_lstnew(void *content);

void	ft_lstadd(t_lst **lst, t_lst *node, int place);

void	ft_lstiter(t_lst *lst, void (*f)(void *));

//		ft_memory.c functions

/**
 * @brief 	set the first (n) bytes of the memory area pointed to by (ptr) to
 *			zero
 *
 * @param ptr 	pointer to the memory area
 * @param n 	number of bytes to set to zero
 */
void	ft_bzero(void *ptr, size_t n);
/**
 * @brief 	set the first (n) bytes of the memory area pointed to by (ptr) to
 *			the value (val)
 *
 * @param ptr 	pointer to the memory area
 * @param val	value to set the bytes at
 * @param n 	number of bytes to set to val
 */
void	ft_memset(void *ptr, int val, size_t n);
/**
 * @brief 	copies the first (n) bytes from memory area pointed to by (src) to
 *			memory area pointed to by (dst)
 *
 * @param dst 	memory area copying to
 * @param src 	memory area copying from
 * @param n 	number of bytes to copy
 */
void	ft_memmove(void *dst, const void *src, size_t n);
/**
 * @brief 	allocate a memory area filled with null bytes for an array of (n)
 *			objects of size (size)
 *
 * @param n 	number of objects
 * @param size 	size of objects
 * @return 		pointer to the memory area allocated
 */
void	*ft_calloc(size_t n, size_t size);
/**
 * @brief 	reallocate the memory area pointed to by (ptr) for an array of (n)
 *			objects of size (size)
 *
 * @param ptr 	memory area to reallocate
 * @param n 	number of objects
 * @param size 	size of objects
 * @return 		pointer to the memory area reallocated
 */
void	*ft_realloc(void *ptr, size_t count, size_t size);

//		ft_put_fd.c functions

/**
 * @brief 	writes the character (c) to the output (fd)
 *
 * @param fd 	file descriptor
 * @param c 	character to write
 */
void	ft_putchar_fd(int fd, char c);
/**
 * @brief 	writes the (c) character-terminated string (str) to the output (fd)
 *
 * @param fd 	file descriptor
 * @param str 	string to write
 * @param c 	end character
 */
void	ft_putsub_fd(int fd, const char *str, char c);
/**
 * @brief 	writes the number (nbr) to the output (fd)
 *
 * @param fd 	file descriptor
 * @param nbr 	number to write
 */
void	ft_putnbr_fd(int fd, int nbr);
/**
 * @brief 	writes the unsigned number (nbr) to the output (fd)
 *
 * @param fd 	file descriptor
 * @param nbr 	unsigned number to write
 */
void	ft_putunbr_fd(int fd, size_t nbr);
/**
 * @brief 	writes the unsigned number (nbr) under the new base (base) to the
 * 			output (fd)
 *
 * @param fd 	file descriptor
 * @param nbr 	unsigned number to write
 * @param base 	new base
 */
void	ft_putunbrbase_fd(int fd, size_t nbr, const char *base);

//		ft_str_new.c functions

/**
 * @brief 	duplicates the string (src)
 *
 * @param src 	string to duplicate
 * @return 		duplicate of str
 */
char	*ft_strdup(const char *src);

char	*ft_strcut(char *src, size_t start, size_t size, int clean);
/**
 * @brief 	duplicates a substring of the string (src), starting at the index
 *			(start) and with a lenght of (len)
 *
 * @param src 	string
 * @param start index to start the substring
 * @param len 	lenght of the substring
 * @return 		substring of str
 */
char	*ft_substr(const char *src, size_t start, size_t len);
/**
 * @brief 	join the strings (s1) and (s2) into a new string
 *
 * @param s1 		first string to join
 * @param s2 		second string to join
 * @param clean_s1 	set to 1 to free s1
 * @param clean_s2 	set to 1 to free s2
 * @return 			string containing s2 at the end of s1
 */
char	*ft_strjoin(char *s1, char *s2, int clean_s1, int clean_s2);
/**
 * @brief 	join multiple strings into a new string
 *
 * @param clean binary chain indicating wich strings to clean or not
 * @param ... 	strings to join
 * @return 		string containing all the strings concatenated together
 */
char	*ft_multijoin(char *clean, ...);

//		ft_str_read.c functions

/**
 * @brief 	returns a pointer to the substring starting at (the first occurrence
 *			of the character (c) + (gap)) in the string (str)
 *
 * @param str 	string to search in
 * @param c 	researched character
 * @param gap 	gap between the first occurence of c and the start of the
 * 				substring
 * @return 		pointer to the first occurrence of c
 */
char	*ft_strchr(const char *str, char c, int gap);
/**
 * @brief 	returns a pointer to the substring starting at (the last occurrence
 *			of the character (c) + (gap)) in the string (str)
 *
 * @param str 	string to search in
 * @param c 	researched character
 * @param gap 	gap between the last occurence of c and the start of the
 *				substring
 * @return 		pointer to the last occurrence of c
 */
char	*ft_strrchr(const char *str, char c, int gap);
/**
 * @brief 	finds the first occurrence of the substring (sub) in the (n) first
 *			character of the string (str)
 *
 * @param str 	string to search in
 * @param sub 	researched substring
 * @param n 	number of character to look into
 * @return 		pointer to the first occurence of sub
 */
char	*ft_strnstr(const char *str, const char *sub, size_t len);
/**
 * @brief 	compares the first (n) characters of the two strings (s1) and (s2)
 *
 * @param s1 	first string
 * @param s2 	second string
 * @param n 	number of bytes to compare
 * @return 		difference between the first varying character of s1 and s2
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//		ft_str_write.c functions

/**
 * @brief 	copies up to ((dstsize) - 1) characters from the string (src) to
 *			(dst)
 *
 * @param dst 		destination string
 * @param src 		source string
 * @param dstsize 	max size of the final dst
 * @return			length of the string attempted to create
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
/**
 * @brief 	concatenate up to ((dstsize) - lenght of src - 1) characters from
 *			the string (src) to the end of the string (dst)
 *
 * @param dst 		destination string
 * @param src 		source string
 * @param dstsize 	max size of the final dst
 * @return 			length of the string attempted to create
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
/**
 * @brief 	remove the characters in (set) at the start and at the end of the
 *			string (str)
 *
 * @param src 			string to trim
 * @param set 			set of characters to remove
 * @param clean_src 	set to 1 to free src
 * @return 				trimed str
 */
char	*ft_strtrim(char *s1, char const *set, int clean);

#endif
