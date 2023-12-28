#include "libft.h"

char	**ft_tabadd(char **tab, char *to_add, int do_free)
{
	char	**tmp;
	int		i;

	i = -1;
	while (tab[++i])
		;
	tmp = malloc ((i + 2) * sizeof (char *));
	i = -1;
	while (tab[++i])
	{
		tmp[i] = ft_strdup(tab[i]);
		if (do_free && tab[i])
			free (tab[i]);
	}
	tmp[i] = ft_strdup(to_add);
	if (do_free)
		free (tab);
	tmp[i + 1] = NULL;
	return (tmp);
}
