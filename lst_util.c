/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:08 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/28 10:28:39 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstnew(char *str)
{
	t_token	*token;

	if (str == NULL)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = str;
	token->before = NULL;
	token->next = NULL;
	token->command = 0;
	token->file = 0;
	token->option = 0;
	token->op = 0;
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
		free(temp->str);
		temp = temp->next;
		before->next = NULL;
		before->before = NULL;
		free(before);
	}
	*lst = NULL;
	return ;
}

void	printlst(t_token **p_token)
{
	t_token	*token;

	if (p_token == NULL)
		return ;
	token = *p_token;
	printf("\n");
	while (token != NULL)
	{
		printf("before : %p\nnow : %p\nstr : %s\ncmd = %d\nopt = %d\nfile = %d\nop = %d\nnext : %p\nnow : %p\n\n", token->before, token, token->str, token->command, token->option, token->file, token->op, token->next, token);
		token = token->next;
	}
	return ;
}
