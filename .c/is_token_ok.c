/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_ok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:36:30 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/28 13:52:58 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double(t_token *token)
{
	if (token->op > 0)
	{
		if (token->next != NULL && token->next->op > 0 && (is_redirection(token->next->str) != 1 && token->str[0] == '|'))
		{
			printf("Syntax error near unexpected token : ");
			printf("\'%s\'\n", token->next->str);
			return (1);
		}
	}
	return (0);
}

int	is_red_ok(t_token *token)
{
	if (is_redirection(token->str) == 1)
	{
		if (token->next == NULL || token->next->file != 1)
			return (syntax_error(token, AFTER), 1);
	}
	return (0);
}

int	is_pipe_ok(t_token *token)
{
	t_token	*temp;
	
	if (token->before == NULL && token->op == 1 && token->str[0] == '|')
		return (syntax_error(token, BEFORE), 1);
	temp = lstlast(token);
	if (temp->op == 1 && temp->str[0] == '|')
		return (syntax_error(temp, AFTER), 1);
	return (0);
}
