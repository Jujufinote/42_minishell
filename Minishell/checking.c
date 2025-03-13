/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:04:19 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 11:58:21 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checking(t_token *token)
{
	while (token != NULL)
	{
		if (is_double(token) == 1)
			return (1);
		if (is_red_ok(token) == 1)
			return (1);
		if (is_pipe_ok(token) == 1)
			return (1);
		token = token->next;
	}
	return (0);
}

int	is_double(t_token *token)
{
	if (token->op > 0)
	{
		if (token->next != NULL && token->next->op > 0 \
		&& (is_redirection(token->next->str) != 1 && token->str[0] == '|'))
			return (syntax_error(token), 1);
	}
	return (0);
}

int	is_red_ok(t_token *token)
{
	if (is_redirection(token->str) == 1)
	{
		if (token->next == NULL || token->next->file != 1)
			return (syntax_error(token), 1);
	}
	return (0);
}

int	is_pipe_ok(t_token *token)
{
	t_token	*temp;

	if (token->before == NULL && token->op == 1 && token->str[0] == '|')
		return (syntax_error(token), 1);
	temp = lstlast(token);
	if (temp->op == 1 && temp->str[0] == '|')
		return (syntax_error(temp), 1);
	return (0);
}
