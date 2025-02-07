/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:37:25 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 11:22:09 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*p_new_lst;
	void	*res_content;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	new_node = NULL;
	p_new_lst = new_node;
	while (lst != NULL)
	{
		res_content = f(lst->content);
		new_node = ft_lstnew(res_content);
		if (new_node == NULL)
		{
			ft_lstdelone(new_node, del);
			return (NULL);
		}
		ft_lstadd_back(&p_new_lst, new_node);
		lst = lst->next;
	}
	return (p_new_lst);
}
