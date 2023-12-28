/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:49:03 by hvincent          #+#    #+#             */
/*   Updated: 2021/11/06 11:49:08 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newstr;
	t_list	*temp;

	if (lst && f)
	{
		newstr = ft_lstnew(f(lst->content));
		temp = newstr;
		while (lst->next)
		{
			lst = lst->next;
			temp->next = ft_lstnew(f(lst->content));
			if (!temp)
			{
				ft_lstclear(&newstr, del);
				return (NULL);
			}
			temp = temp->next;
		}
		return (newstr);
	}
	return (NULL);
}
