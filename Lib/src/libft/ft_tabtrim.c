#include "libft.h"

int	ft_strdiffstr(char *str, char *to_search)
{
	int	i;
	int	j;
	int	find;

	i = -1;
	while (str[++i])
	{
		find = 0;
		j = -1;
		while (to_search[++j])
			if (str[i] == to_search[j])
				find = 1;
		if (find == 0)
			return (1);
	}
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_tabtrim(char **tab, char *keep_set, int do_free)
{
	int		before;
	int		j;
	int		i;
	char	**tmp;

	before = 0;
	while (tab[before] && !ft_strdiffstr(tab[before], keep_set))
		before++;
	i = ft_tablen(tab) - 1;
	while (i > before && !ft_strdiffstr(tab[i], keep_set))
		i--;
	if (i <= before)
		return (0);
	tmp = malloc(((i - before) + 2) * sizeof(char *));
	j = 0;
	while (before <= i)
		tmp[j++] = ft_strdup(tab[before++]);
	tmp[j] = NULL;
	i = -1;
	if (do_free)
		while (tab[++i])
			free (tab[i]);
	if (do_free)
		free(tab);
	return (tmp);
}
