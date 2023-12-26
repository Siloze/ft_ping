/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:27:38 by mbastard          #+#    #+#             */
/*   Updated: 2022/09/06 23:01:05 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*lst;

	lst = (t_lst *)malloc(sizeof(t_lst));
	lst->content = content;
	lst->previous = NULL;
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd(t_lst **lst, t_lst *node, int place)
{
	int		i;
	t_lst	*view;

	i = -1;
	view = *lst;
	if (place == -1)
		while (view->next)
			view = view->next;
	else
		while (++i < place && view->next)
			view = view->next;
	node->previous = view;
	node->next = view->next;
	view->next = node;
}

void	ft_lstiter(t_lst *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
