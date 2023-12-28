#include "libft.h"

char	*ft_strchrstr(char *src, const char *search, size_t len)
{
	unsigned int	i;

	i = -1;
	if (!ft_strlen(src, '\0') || !ft_strlen(search, '\0'))
		return (0);
	if (!src || !search || !len)
		return (0);
	while ((src[++i]))
		if (!ft_strncmp(&src[i], search, len))
			return (&src[i]);
	return (0);
}
