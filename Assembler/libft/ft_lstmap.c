/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:02:28 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/10 16:13:56 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*funclst;
	t_list	*head;

	if (lst == NULL || f == NULL)
		return (NULL);
	funclst = f(lst);
	new = ft_lstnew(funclst->content, funclst->content_size);
	if (new == NULL)
		return (NULL);
	lst = lst->next;
	head = new;
	while (lst != NULL)
	{
		funclst = f(lst);
		new->next = ft_lstnew(funclst->content, funclst->content_size);
		if (new->next == NULL)
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	return (head);
}
