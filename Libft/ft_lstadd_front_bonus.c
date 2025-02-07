/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:36:50 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 11:23:29 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
		new->next = NULL;
	else
		new->next = *lst;
	*lst = new;
	return ;
}

/* lst = l'adresse du pointeur sur le premier lien d'une liste
   new = l'adresse d'un pointeur sur le noeud qui doit être ajouté
   premier lien d'une liste est appelé "porteur de tête", c'est le
   point de départ d'une liste, la toute première structure enregistrée*/
