/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:08 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/01 17:47:30 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstnew(char *base, char *post_str)
{
	t_token	*token;

	if (post_str == NULL)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->base = base;
	token->post_str = post_str;
	token->str = NULL;
	token->op = 0;
	token->file = 0;
	token->next = NULL;
	token->before = NULL;
	return (token);
}

void	lstadd_back(t_token	**token, t_token *new)
{
	t_token	*last;

	last = lstlast(*token);
	if (last == NULL)
		*token = new;
	else
	{
		last->next = new;
		new->before = last;
	}
	return ;
}

t_token	*lstlast(t_token *token)
{
	t_token	*temp;
	t_token	*before;

	if (token == NULL)
		return (token);
	temp = token;
	while (temp != NULL)
	{
		before = temp;
		temp = temp->next;
	}
	return (before);
}

void	lstdel(t_token **lst)
{
	t_token	*temp;
	t_token	*before;

	if (lst == NULL)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		before = temp;
		free(temp->base);
		free(temp->post_str);
		free(temp->str);
		temp = temp->next;
		before->next = NULL;
		before->before = NULL;
		free(before);
	}
	*lst = NULL;
	return ;
}
