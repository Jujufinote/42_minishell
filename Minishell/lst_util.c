/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:08 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 11:53:22 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstnew(char *base, char *str)
{
	t_token	*token;

	if (str == NULL)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->base = base;
	token->str = str;
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
		free(temp->str);
		temp = temp->next;
		before->next = NULL;
		before->before = NULL;
		free(before);
	}
	*lst = NULL;
	return ;
}

/*void	printlst(t_token **p_token)
{
	t_token	*token;

	if (p_token == NULL)
		return ;
	token = *p_token;
	printf("\n");
	while (token != NULL)
	{
		printf("before : %p\nnow : %p\nbase : %s\nstr : %s\nop = %d\n
		file = %d\nnext : %p\nnow : %p\n\n", token->before, token, token->base, 
		token->str, token->op, token->file, token->next, token);
		token = token->next;
	}
	return ;
}*/
